#ifndef FILES_H_CfN2FMhCDWuDXQYkXS4DRLcNv7kd9VzL
#define FILES_H_CfN2FMhCDWuDXQYkXS4DRLcNv7kd9VzL

#include <stddef.h>
#include <efi.h>
#include <efilib.h>

EFI_FILE_HANDLE
get_image_volume(EFI_HANDLE img_handle);

#endif
