#ifndef PAGING_H_aIUR1xkuEFGQiIVZrHEIatoFhtIu6k7e
#define PAGING_H_aIUR1xkuEFGQiIVZrHEIatoFhtIu6k7e

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

#endif
