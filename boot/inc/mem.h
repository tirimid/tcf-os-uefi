#ifndef MEM_H_jYz6n65pkgY8AOq8SpFuTXJDxDoKDwVU
#define MEM_H_jYz6n65pkgY8AOq8SpFuTXJDxDoKDwVU

#include <stddef.h>

#define PAGE_SIZE 0x1000

void *
alloc_page(void *phys_addr);

void *
alloc_pages(void *phys_addr, size_t cnt);

void
free_page(const void *page);

void
free_pages(const void *page, size_t cnt);

void *
alloc_pool_mem(size_t size);

void
free_pool_mem(void *buf);

#endif
