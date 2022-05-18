#ifndef MEM_PGALLOC_H__
#define MEM_PGALLOC_H__

#include "common/mem.h"
#include <stddef.h>

void pgalloc_init(const struct mem_map *mem_map, size_t _page_size);

void *pgalloc_request_page(void);
void *pgalloc_request_pages(size_t page_cnt);
void *pgalloc_request_zero_page(void);
void *pgalloc_request_zero_pages(size_t page_cnt);

void pgalloc_reserve_page(void *page);
void pgalloc_reserve_pages(void *page, size_t page_cnt);

void pgalloc_free_page(void *page);
void pgalloc_free_pages(void *page, size_t page_cnt);

#endif
