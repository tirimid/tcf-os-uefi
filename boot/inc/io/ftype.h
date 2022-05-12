#ifndef BOOT_IO_FTYPE_H
#define BOOT_IO_FTYPE_H

#include <efi.h>
#include <efilib.h>
#include "comgfx.h"

/* buffer of psf font must be freed after use */
struct com_gfx_psf_font io_ftype_read_psf_font_file(EFI_FILE_HANDLE file);

enum io_ftype_elf_header_inst_set {
        ELF_HEADER_INST_SET_NONE = 0x0,
        ELF_HEADER_INST_SET_X86 = 0x3,
        ELF_HEADER_INST_SET_X86_64 = 0x3e,
};

enum io_ftype_elf_header_type {
        ELF_HEADER_TYPE_RELOCATABLE = 1,
        ELF_HEADER_TYPE_EXECUTABLE = 2,
        ELF_HEADER_TYPE_SHARED = 3,
        ELF_HEADER_TYPE_CORE = 4,
};

/* returns entry point for elf file */
void *io_ftype_load_elf_file(EFI_FILE_HANDLE file, enum io_ftype_elf_header_inst_set inst_set,
                             enum io_ftype_elf_header_type type);

#endif
