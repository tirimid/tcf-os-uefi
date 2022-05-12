#ifndef BOOT_IO_FILES_H
#define BOOT_IO_FILES_H

#include <stddef.h>
#include <efi.h>
#include <efilib.h>

EFI_FILE_HANDLE io_files_image_volume(EFI_HANDLE img_handle);

EFI_FILE_HANDLE io_files_open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name);
void io_files_close_file(EFI_FILE_HANDLE file);

void *io_files_read_file(EFI_FILE_HANDLE file, void *dst, uintptr_t offset, size_t size);
size_t io_files_file_size(EFI_FILE_HANDLE file);

#endif
