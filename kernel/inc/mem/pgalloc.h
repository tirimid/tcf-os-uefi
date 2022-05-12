#ifndef KERNEL_MEM_PGALLOC_H
#define KERNEL_MEM_PGALLOC_H

#include "commem.h"
#include <stddef.h>

void mem_pgalloc_init(struct com_mem_map *mem_map, size_t _page_size);

void *mem_pgalloc_request_page(void);
void *mem_pgalloc_request_pages(size_t page_cnt);
void mem_pgalloc_lock_page(void *page);
void mem_pgalloc_lock_pages(void *page, size_t page_cnt);
void mem_pgalloc_unlock_page(void *page);
void mem_pgalloc_unlock_pages(void *page, size_t page_cnt);

#endif