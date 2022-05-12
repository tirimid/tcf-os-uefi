#ifndef BOOT_BOOT_CTL_H
#define BOOT_BOOT_CTL_H

#include <efi.h>
#include <efilib.h>
#include "comboot.h"

void boot_ctl_init(EFI_SYSTEM_TABLE *sys_table);
void boot_ctl_exit(EFI_HANDLE img_handle);
struct com_boot_info boot_ctl_info(EFI_HANDLE img_handle);

#endif
