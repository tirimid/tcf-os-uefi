#include "io/ftype.h"

#include <efi.h>
#include <efilib.h>
#include "mem/page.h"
#include "mem/pool.h"
#include "lcstring.h"
#include "io/file.h"
#include <stdbool.h>
#include "io/text.h"

/* buffer of psf font must be freed after use */
struct gfx_psf_font ftype_read_psf_font(EFI_FILE_HANDLE file)
{
        struct gfx_psf_font font;

        file_read(file, &font, 0, sizeof(font.hdr));
        
        if (font.hdr.magic != 0x864ab572)
                text_log_error(L"read invalid font header");
        
        size_t glyph_buf_size = font.hdr.glyph_bytes * font.hdr.glyph_cnt;
        
        font.glyph_buf = pool_alloc(glyph_buf_size);
        file_read(file, font.glyph_buf, sizeof(font.hdr), glyph_buf_size);
        
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
void *ftype_load_elf(EFI_FILE_HANDLE file, enum ftype_elf_header_inst_set inst_set,
                     enum ftype_elf_header_type type)
{
        struct elf_header elf_hdr;
        file_read(file, &elf_hdr, 0, sizeof(elf_hdr));

        bool hdr_valid = elf_hdr.inst_set == inst_set && elf_hdr.type == type
                         && memcmp("\x7f" "ELF", (char *)&elf_hdr.magic, 4) == 0;
        
        if (!hdr_valid)
                text_log_error(L"read invalid elf header");

        size_t prog_hdrs_size = elf_hdr.prog_hdr_cnt * elf_hdr.prog_hdr_size;
        struct elf_prog_header *prog_hdrs = pool_alloc(prog_hdrs_size);
        
        file_read(file, prog_hdrs, elf_hdr.prog_hdr_table_pos, prog_hdrs_size);

        for (int i = 0; i < elf_hdr.prog_hdr_cnt; ++i) {
                switch (prog_hdrs[i].type) {
                case ELF_PROG_HEADER_TYPE_LOAD:;
                        size_t page_cnt = (prog_hdrs[i].size_mem) / PAGE_SIZE;
                        void *hdr_virt_addr = (void *)prog_hdrs[i].virt_addr;
                        void *hdr_addr = page_alloc(hdr_virt_addr, page_cnt);

                        file_read(file, hdr_addr, prog_hdrs[i].file_offset, prog_hdrs[i].size_file);
                        
                        break;
                }
        }
        
        pool_free(prog_hdrs);
        
        return (void *)elf_hdr.prog_entry_pos;
}
