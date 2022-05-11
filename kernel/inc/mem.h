#ifndef MEM_H_kXA3zveBskz7WjXcxvcJXplbfmY5L8D5
#define MEM_H_kXA3zveBskz7WjXcxvcJXplbfmY5L8D5

#include "common.h"

/* =============
 * mem_pgalloc.c
 * =============
 */

void mem_pgalloc_init(const struct com_mem_map *mem_map, int _page_size);

void *mem_pgalloc_request_page(void);
void mem_pgalloc_lock_page(void *page);
void mem_pgalloc_unlock_page(void *page);

/* ==========
 * mem_page.c
 * ==========
 */

/* ==========
 * mem_heap.c
 * ==========
 */

#endif
