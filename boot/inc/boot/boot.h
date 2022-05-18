#ifndef BOOT_BOOT_H__
#define BOOT_BOOT_H__

#include <efi.h>
#include <efilib.h>
#include "common/boot.h"

void boot_init(EFI_SYSTEM_TABLE *sys_table);
void boot_exit(EFI_HANDLE img_handle);
struct boot_info boot_info(EFI_HANDLE img_handle);

#endif
