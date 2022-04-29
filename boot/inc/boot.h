#ifndef BOOT_H_EACrsrZeXTHS01nlp7VKIZHBYMWwJ2Dm
#define BOOT_H_EACrsrZeXTHS01nlp7VKIZHBYMWwJ2Dm

#include <efi.h>
#include <efilib.h>
#include <stddef.h>
#include "boottypes.h"

void
init_boot(EFI_SYSTEM_TABLE *sys_table);

const wchar_t *
boot_version(void);

void
exit_boot(EFI_HANDLE img_handle);

struct boot_info
retrieve_boot_info(EFI_HANDLE img_handle);

#endif
