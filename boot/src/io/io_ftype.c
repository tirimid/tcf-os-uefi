#include "io.h"

#include <efi.h>
#include <efilib.h>
#include "mem.h"
#include "lcstring.h"

/* buffer of psf font must be freed after use */
struct com_gfx_psf_font io_ftype_read_psf_font_file(EFI_FILE_HANDLE file)
{
        struct com_gfx_psf_font font;

        io_files_read_file(file, &font, 0, sizeof(font.hdr));
        
        if (font.hdr.magic != 0x864ab572)
                io_text_log_error(L"read invalid font header");
        
        size_t glyph_buf_size = font.hdr.glyph_bytes * font.hdr.glyph_cnt;
        
        font.glyph_buf = mem_pool_alloc_mem(glyph_buf_size);
        io_files_read_file(file, font.glyph_buf, sizeof(font.hdr), glyph_buf_size);
        
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
void *io_ftype_load_elf_file(EFI_FILE_HANDLE file, enum io_ftype_elf_header_inst_set inst_set,
                             enum io_ftype_elf_header_type type)
{
        struct elf_header elf_hdr;
        io_files_read_file(file, &elf_hdr, 0, sizeof(elf_hdr));

        bool hdr_valid = elf_hdr.inst_set == inst_set && elf_hdr.type == type
                         && memcmp("\x7f" "ELF", (char *)&elf_hdr.magic, 4) == 0;
        
        if (!hdr_valid)
                io_text_log_error(L"read invalid elf header");

        size_t prog_hdrs_size = elf_hdr.prog_hdr_cnt * elf_hdr.prog_hdr_size;
        struct elf_prog_header *prog_hdrs = mem_pool_alloc_mem(prog_hdrs_size);
        
        io_files_read_file(file, prog_hdrs, elf_hdr.prog_hdr_table_pos, prog_hdrs_size);

        for (int i = 0; i < elf_hdr.prog_hdr_cnt; ++i) {
                switch (prog_hdrs[i].type) {
                case ELF_PROG_HEADER_TYPE_LOAD:;
                        size_t page_cnt = (prog_hdrs[i].size_mem) / PAGE_SIZE;
                        void *hdr_virt_addr = (void *)prog_hdrs[i].virt_addr;
                        void *hdr_addr = mem_page_alloc_pages(hdr_virt_addr, page_cnt);

                        io_files_read_file(file, hdr_addr, prog_hdrs[i].file_offset,
                                           prog_hdrs[i].size_file);
                        
                        break;
                }
        }
        
        mem_pool_free_mem(prog_hdrs);
        
        return (void *)elf_hdr.prog_entry_pos;
}
