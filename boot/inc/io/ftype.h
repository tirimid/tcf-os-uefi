#ifndef IO_FTYPE_H__
#define IO_FTYPE_H__

#include <efi.h>
#include <efilib.h>
#include "common/gfx.h"

/* buffer of psf font must be freed after use */
struct gfx_psf_font ftype_read_psf_font(EFI_FILE_HANDLE file);

enum ftype_elf_header_inst_set {
        FTYPE_ELF_HEADER_INST_SET_NONE = 0x0,
        FTYPE_ELF_HEADER_INST_SET_X86 = 0x3,
        FTYPE_ELF_HEADER_INST_SET_X86_64 = 0x3e,
};

enum ftype_elf_header_type {
        FTYPE_ELF_HEADER_TYPE_RELOCATABLE = 1,
        FTYPE_ELF_HEADER_TYPE_EXECUTABLE = 2,
        FTYPE_ELF_HEADER_TYPE_SHARED = 3,
        FTYPE_ELF_HEADER_TYPE_CORE = 4,
};

/* returns entry point for elf file */
void *ftype_load_elf(EFI_FILE_HANDLE file, enum ftype_elf_header_inst_set inst_set,
                     enum ftype_elf_header_type type);

#endif
