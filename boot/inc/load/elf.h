#ifndef ELF_H_HZ99DeDOHatwSF1Ppse5AloYqQIHTMzA
#define ELF_H_HZ99DeDOHatwSF1Ppse5AloYqQIHTMzA

#include <stdint.h>
#include <stdbool.h>

/* 64 bit variant */
__attribute__((packed)) struct elf_header {
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

bool
is_elf_header_valid(const struct elf_header *elf_hdr);

/* 64 bit variant */
__attribute__((packed)) struct elf_prog_header {
        uint32_t type;
        uint32_t flags;
        uint64_t file_offset;
        uint64_t virt_addr;
        uint64_t _ignore;
        uint64_t size_file;
        uint64_t size_mem;
        uint64_t req_align;
};

#endif
