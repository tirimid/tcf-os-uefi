#ifndef PAGING_H_Af5iFIPPEKhqAkVymSf40Ng1k2PRIOhi
#define PAGING_H_Af5iFIPPEKhqAkVymSf40Ng1k2PRIOhi

#include <stddef.h>

#define PAGE_SIZE EFI_PAGE_SIZE

void *
alloc_page(void *phys_addr);

void *
alloc_pages(void *phys_addr, size_t cnt);

#endif
