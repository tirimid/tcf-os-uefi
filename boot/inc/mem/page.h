#ifndef _MEM_PAGE_H_
#define _MEM_PAGE_H_

#include <stddef.h>
#include <efi.h>
#include <efilib.h>

#define PAGE_SIZE EFI_PAGE_SIZE

void *page_alloc(void *phys_addr, size_t page_cnt);

#endif
