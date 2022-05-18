#ifndef MEM_PAGE_H__
#define MEM_PAGE_H__

#include <stddef.h>
#include <efi.h>
#include <efilib.h>

#define PAGE_SIZE EFI_PAGE_SIZE

void *page_alloc(void *phys_addr, size_t page_cnt);

#endif
