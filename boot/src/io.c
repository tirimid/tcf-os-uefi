#include "io.h"

#include <stdbool.h>
#include "string.h"
#include "mem.h"

#define LOG_PREFIX L"[ tcf-boot-uefi ]"
#define PRINT_BUF_SIZE 512
#define FILE_NAME_BUF_SIZE 256
#define FILE_INFO_BUF_SIZE 128
#define PSF_FONT_HEADER_MAGIC 0x864ab572
#define ELF_HEADER_MAGIC "\x7f" "ELF"

static wchar_t print_buf[PRINT_BUF_SIZE] = { L'\0' };

void
print(const wchar_t *s)
{
        wcscpy(print_buf, s); /* allow const string as argument in function */
        ST->ConOut->OutputString(ST->ConOut, print_buf);
}

void
print_line(const wchar_t *s)
{
        print(s);
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
}

void
log_info(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" info: ");
        print_line(s);
}

void
log_error(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" error: ");
        print_line(s);

        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}

EFI_FILE_HANDLE
image_volume(EFI_HANDLE img_handle)
{
        EFI_LOADED_IMAGE *loaded_img;
        EFI_GUID lip_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;

        BS->HandleProtocol(img_handle, &lip_guid, (void **)&loaded_img);
        
        EFI_GUID fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
        EFI_FILE_IO_INTERFACE *vol_iface;
        
        BS->HandleProtocol(loaded_img->DeviceHandle, &fs_guid,
                           (void **)&vol_iface);
        
        EFI_FILE_HANDLE vol;
        
        vol_iface->OpenVolume(vol_iface, &vol);
        
        return vol;
}

static wchar_t file_name_buf[FILE_NAME_BUF_SIZE] = { L'\0' };

EFI_FILE_HANDLE
open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name)
{
        /* buffer is used to allow const file_name argument */
        wcscpy(file_name_buf, file_name);
        
        EFI_FILE_HANDLE file;
        
        vol->Open(vol, &file, file_name_buf, EFI_FILE_MODE_READ,
                  EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
        
        return file;
}

void *
read_file(EFI_FILE_HANDLE file, void *dst, uintptr_t offset, size_t size)
{
        file->SetPosition(file, offset);
        file->Read(file, &size, dst);

        return dst;
}

void
close_file(EFI_FILE_HANDLE file)
{
        file->Close(file);
}

/* file info is read into a very large buffer to ensure enough size */
static uint8_t file_info_buf[FILE_INFO_BUF_SIZE];

size_t
file_size(EFI_FILE_HANDLE file)
{
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)file_info_buf;
        size_t buf_size = FILE_INFO_BUF_SIZE;

        file->GetInfo(file, &GenericFileInfo, &buf_size, info);
        
        return info->FileSize;
}

static inline bool
is_psf_font_header_valid(const struct psf_font_header *hdr)
{
        return hdr->magic == PSF_FONT_HEADER_MAGIC;
}

/* buffer of psf font must be freed after use */
struct psf_font
read_psf_font_file(EFI_FILE_HANDLE file)
{
        struct psf_font font;
        
        read_file(file, &font, 0, sizeof(font.hdr));
        
        if (!is_psf_font_header_valid(&font.hdr))
                log_error(L"read_psf_font_file(): read invalid font header");
        
        size_t glyph_buf_size = font.hdr.glyph_bytes * font.hdr.glyph_cnt;
        
        font.glyph_buf = alloc_pool_mem(glyph_buf_size);
        read_file(file, font.glyph_buf, sizeof(font.hdr), glyph_buf_size);
        
        return font;
}

/* 64 bit variant */
struct __attribute__((packed)) elf_header {
        uint32_t magic;
        uint8_t bits;
        uint8_t endianness;
        uint8_t hdr_ver;
        uint8_t abi;
        uint64_t _ignore;
        uint16_t type;
        uint16_t inst_set;
        uint32_t elf_ver;
        uint64_t prog_entry_pos;
        uint64_t prog_hdr_table_pos;
        uint64_t sect_hdr_table_pos;
        uint32_t flags;
        uint16_t hdr_size;
        uint16_t prog_hdr_size;
        uint16_t prog_hdr_cnt;
        uint16_t sect_hdr_size;
        uint16_t sect_hdr_cnt;
        uint16_t names_sect_hdr_ind;
};

static bool
is_elf_header_valid(const struct elf_header *elf_hdr,
                    enum elf_header_inst_set inst_set,
                    enum elf_header_type type)
{
        int magic_cmp = memcmp(ELF_HEADER_MAGIC,
                               (const char *)&elf_hdr->magic, 4);

        return magic_cmp == 0 && elf_hdr->inst_set == inst_set
               && elf_hdr->type == type;
}

enum elf_prog_header_type {
        ELF_PROG_HEADER_TYPE_NULL = 0,
        ELF_PROG_HEADER_TYPE_LOAD = 1,
        ELF_PROG_HEADER_TYPE_DYNAMIC = 2,
        ELF_PROG_HEADER_TYPE_INTERP = 3,
        ELF_PROG_HEADER_TYPE_NOTE = 4,
};

/* 64 bit variant */
struct __attribute__((packed)) elf_prog_header {
        uint32_t type;
        uint32_t flags;
        uint64_t file_offset;
        uint64_t virt_addr;
        uint64_t _ignore;
        uint64_t size_file;
        uint64_t size_mem;
        uint64_t req_align;
};

/* returns entry point for elf file */
void *
load_elf_file(EFI_FILE_HANDLE file, enum elf_header_inst_set inst_set,
              enum elf_header_type type)
{
        struct elf_header elf_hdr;
       
        read_file(file, &elf_hdr, 0, sizeof(elf_hdr));
        
        if (!is_elf_header_valid(&elf_hdr, inst_set, type))
                log_error(L"load_elf_file(): invalid elf header");

        size_t prog_hdrs_size = elf_hdr.prog_hdr_cnt * elf_hdr.prog_hdr_size;
        struct elf_prog_header *prog_hdrs = alloc_pool_mem(prog_hdrs_size);
        
        read_file(file, prog_hdrs, elf_hdr.prog_hdr_table_pos, prog_hdrs_size);

        for (int i = 0; i < elf_hdr.prog_hdr_cnt; ++i) {
                switch (prog_hdrs[i].type) {
                case ELF_PROG_HEADER_TYPE_LOAD:;
                        size_t page_cnt = (prog_hdrs[i].size_mem) / PAGE_SIZE;
                        void *hdr_virt_addr = (void *)prog_hdrs[i].virt_addr;
                        void *hdr_addr = alloc_pages(hdr_virt_addr, page_cnt);

                        read_file(file, hdr_addr, prog_hdrs[i].file_offset,
                                  prog_hdrs[i].size_file);
                                  
                        break;
                }
        }
        
        free_pool_mem(prog_hdrs);
        
        return (void *)elf_hdr.prog_entry_pos;
}
