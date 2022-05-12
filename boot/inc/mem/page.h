#ifndef BOOT_MEM_PAGE_H
#define BOOT_MEM_PAGE_H

#include <stddef.h>
#include <efi.h>
#include <efilib.h>

#define PAGE_SIZE EFI_PAGE_SIZE

void *mem_page_alloc_page(void *phys_addr);
void *mem_page_alloc_pages(void *phys_addr, size_t cnt);

#endif
