#ifndef IO_H_bSjvz4ioYTwIWqnJaKD9tHwYrGGAKXHU
#define IO_H_bSjvz4ioYTwIWqnJaKD9tHwYrGGAKXHU

#include <stddef.h>
#include "common.h"
#include <efi.h>
#include <efilib.h>

/* ==========
 * io_files.c
 * ==========
 */

EFI_FILE_HANDLE io_files_image_volume(EFI_HANDLE img_handle);

EFI_FILE_HANDLE io_files_open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name);
void io_files_close_file(EFI_FILE_HANDLE file);

void *io_files_read_file(EFI_FILE_HANDLE file, void *dst, uintptr_t offset, size_t size);
size_t io_files_file_size(EFI_FILE_HANDLE file);

/* =========
 * io_text.c
 * =========
 */

void io_text_print(const wchar_t *s);
void io_text_print_line(const wchar_t *s);

void io_text_log_info(const wchar_t *s);
void io_text_log_warning(const wchar_t *s);
void io_text_log_error(const wchar_t *s);

/* ==========
 * io_ftype.c
 * ==========
 */

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
