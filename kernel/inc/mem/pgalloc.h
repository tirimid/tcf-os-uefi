#ifndef KERNEL_MEM_PGALLOC_H
#define KERNEL_MEM_PGALLOC_H

#include "commem.h"
#include <stddef.h>

void mem_pgalloc_init(const struct com_mem_map *mem_map, size_t _page_size);

void *mem_pgalloc_request_page(void);
void *mem_pgalloc_request_pages(size_t page_cnt);
void *mem_pgalloc_request_zero_page(void);
void *mem_pgalloc_request_zero_pages(size_t page_cnt);

void mem_pgalloc_reserve_page(void *page);
void mem_pgalloc_reserve_pages(void *page, size_t page_cnt);

void mem_pgalloc_free_page(void *page);
void mem_pgalloc_free_pages(void *page, size_t page_cnt);

#endif
