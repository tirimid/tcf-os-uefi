#ifndef MEM_H_kXA3zveBskz7WjXcxvcJXplbfmY5L8D5
#define MEM_H_kXA3zveBskz7WjXcxvcJXplbfmY5L8D5

#include "common.h"
#include <stdint.h>

/* =============
 * mem_pgalloc.c
 * =============
 */

void mem_pgalloc_init(struct com_mem_map *mem_map, size_t _page_size);

void *mem_pgalloc_request_page(void);
void *mem_pgalloc_request_pages(int page_cnt);
void mem_pgalloc_lock_page(void *page);
void mem_pgalloc_lock_pages(void *page, int page_cnt);
void mem_pgalloc_unlock_page(void *page);
void mem_pgalloc_unlock_pages(void *page, int page_cnt);

/* ==========
 * mem_page.c
 * ==========
 */

void mem_page_map(void *phys_addr, void *virt_addr);

/* ==========
 * mem_heap.c
 * ==========
 */

void mem_heap_init(void);

void *mem_heap_alloc(size_t size);
void mem_heap_free(void *ptr);

#endif
