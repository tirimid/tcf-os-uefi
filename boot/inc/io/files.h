#ifndef FILES_H_CfN2FMhCDWuDXQYkXS4DRLcNv7kd9VzL
#define FILES_H_CfN2FMhCDWuDXQYkXS4DRLcNv7kd9VzL

#include <stddef.h>
#include <efi.h>
#include <efilib.h>
#include <stddef.h>

EFI_FILE_HANDLE
get_image_volume(EFI_HANDLE img_handle);

EFI_FILE_HANDLE
open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name);

void
read_file(EFI_FILE_HANDLE file, void *dst, size_t size);

void
close_file(EFI_FILE_HANDLE file);

size_t
file_size(EFI_FILE_HANDLE file);

#endif
