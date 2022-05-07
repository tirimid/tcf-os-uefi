#ifndef FILES_H_UrCzvw0UeOOfX3rrzYFd9F2Z7nsOl09e
#define FILES_H_UrCzvw0UeOOfX3rrzYFd9F2Z7nsOl09e

#include <efi.h>
#include <efilib.h>
#include <stddef.h>

EFI_FILE_HANDLE
image_volume(EFI_HANDLE img_handle);

EFI_FILE_HANDLE
open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name);

void *
read_file(EFI_FILE_HANDLE file, void *dst, uintptr_t offset, size_t size);

void
close_file(EFI_FILE_HANDLE file);

#endif
