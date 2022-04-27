#ifndef PAGING_H_aIUR1xkuEFGQiIVZrHEIatoFhtIu6k7e
#define PAGING_H_aIUR1xkuEFGQiIVZrHEIatoFhtIu6k7e

#include <stddef.h>

void *
alloc_page(void);

void *
alloc_pages(size_t cnt);

void
free_page(const void *page);

void
free_pages(const void *page, size_t cnt);

#endif
