#ifndef ELF_H_HZ99DeDOHatwSF1Ppse5AloYqQIHTMzA
#define ELF_H_HZ99DeDOHatwSF1Ppse5AloYqQIHTMzA

#include <stdint.h>

enum elf_header_inst_set {
        ELF_HEADER_INST_SET_NONE = 0x0,
        ELF_HEADER_INST_SET_SPARC = 0x2,
        ELF_HEADER_INST_SET_X86 = 0x3,
        ELF_HEADER_INST_SET_MIPS = 0x8,
        ELF_HEADER_INST_SET_POWERPC = 0x14,
        ELF_HEADER_INST_SET_ARM = 0x28,
        ELF_HEADER_INST_SET_SUPERH = 0x2a,
        ELF_HEADER_INST_SET_IA_64 = 0x32,
        ELF_HEADER_INST_SET_X86_64 = 0x3e,
        ELF_HEADER_INST_SET_AARCH64 = 0xb7,
        ELF_HEADER_INST_SET_RISC_V = 0xf3,
};

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
