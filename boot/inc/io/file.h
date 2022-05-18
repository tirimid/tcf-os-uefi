#ifndef IO_FILE_H__
#define IO_FILE_H__

#include <stddef.h>
#include <efi.h>
#include <efilib.h>

EFI_FILE_HANDLE file_image_volume(EFI_HANDLE img_handle);

EFI_FILE_HANDLE file_open(EFI_FILE_HANDLE vol, const wchar_t *file_name);
void file_close(EFI_FILE_HANDLE file);

void *file_read(EFI_FILE_HANDLE file, void *dst, uintptr_t offset, size_t size);
size_t file_size(EFI_FILE_HANDLE file);

#endif
