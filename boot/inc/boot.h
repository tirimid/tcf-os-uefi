#ifndef BOOT_H_EACrsrZeXTHS01nlp7VKIZHBYMWwJ2Dm
#define BOOT_H_EACrsrZeXTHS01nlp7VKIZHBYMWwJ2Dm

#include <efi.h>
#include <efilib.h>
#include <stddef.h>

void
init_boot(EFI_SYSTEM_TABLE *sys_table);

const wchar_t *
boot_version(void);

#endif
