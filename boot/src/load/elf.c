#include "load/elf.h"

#include <stdint.h>
#include "libc/string.h"
#include "io/files.h"
#include "mem/pool.h"
#include <stdbool.h>
#include "io/text.h"
#include "mem/paging.h"

#define ELF_HEADER_MAGIC "\x7f" "ELF"

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
        uint16_t prog_hdr_table_entry_cnt;
        uint16_t sect_hdr_size;
        uint16_t sect_hdr_table_entry_cnt;
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

enum prog_header_type {
        PROG_HEADER_TYPE_NULL = 0,
        PROG_HEADER_TYPE_LOAD = 1,
        PROG_HEADER_TYPE_DYNAMIC = 2,
        PROG_HEADER_TYPE_INTERP = 3,
        PROG_HEADER_TYPE_NOTE = 4,
};

/* 64 bit variant */
struct __attribute__((packed)) prog_header {
        uint32_t type;
        uint32_t flags;
        uint64_t file_offset;
        uint64_t virt_addr;
        uint64_t _ignore;
        uint64_t size_file;
        uint64_t size_mem;
        uint64_t req_align;
};

static inline struct elf_header
file_elf_header(EFI_FILE_HANDLE file)
{
        struct elf_header hdr;
        read_file(file, &hdr, 0, sizeof(hdr));
        return hdr;
}

/* returned resource must be freed */
static struct prog_header *
file_prog_headers(EFI_FILE_HANDLE file, const struct elf_header *elf_hdr)
{
        size_t prog_hdrs_size = elf_hdr->prog_hdr_table_entry_cnt
                                * elf_hdr->prog_hdr_size;
        struct prog_header *hdrs = alloc_pool_mem(prog_hdrs_size);
        read_file(file, hdrs, elf_hdr->prog_hdr_table_pos, prog_hdrs_size);
        return hdrs;
}

static void
load_prog_header(EFI_FILE_HANDLE file, const struct prog_header *prog_hdr)
{
        switch (prog_hdr->type) {
        case PROG_HEADER_TYPE_LOAD:;
                size_t page_cnt = (prog_hdr->size_mem) / PAGE_SIZE;
                void *hdr_addr = alloc_pages((void *)prog_hdr->virt_addr,
                                             page_cnt);
                read_file(file, hdr_addr, prog_hdr->file_offset,
                          prog_hdr->size_file);
                break;
        }
}

/* returns entry point for elf file */
void *
load_elf_file(EFI_FILE_HANDLE file, enum elf_header_inst_set inst_set,
              enum elf_header_type type)
{
        struct elf_header elf_hdr = file_elf_header(file);
        if (!is_elf_header_valid(&elf_hdr, inst_set, type))
                log_error(L"load_elf_file(): invalid elf header");
        struct prog_header *prog_hdrs = file_prog_headers(file, &elf_hdr);
        for (int i = 0; i < elf_hdr.prog_hdr_table_entry_cnt; ++i) {
                const struct prog_header *hdr = (const struct prog_header *)(
                                                (uintptr_t)prog_hdrs + i
                                                * elf_hdr.prog_hdr_size);
                load_prog_header(file, hdr);
        }
        free_pool_mem(prog_hdrs);
        return (void *)elf_hdr.prog_entry_pos;
}
