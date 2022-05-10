#ifndef BOOT_H_EACrsrZeXTHS01nlp7VKIZHBYMWwJ2Dm
#define BOOT_H_EACrsrZeXTHS01nlp7VKIZHBYMWwJ2Dm

#include <efi.h>
#include <efilib.h>
#include <stddef.h>
#include "common.h"

/* ==========
 * boot_ctl.c
 * ==========
 */

void boot_ctl_init(EFI_SYSTEM_TABLE *sys_table);
void boot_ctl_exit(EFI_HANDLE img_handle);
struct com_boot_info boot_ctl_info(EFI_HANDLE img_handle);

#endif
