#ifndef KERNEL_MEM_PGALLOC_H
#define KERNEL_MEM_PGALLOC_H

#include "commem.h"

void mem_pgalloc_init(const struct com_mem_map *mem_map, int _page_size);

void *mem_pgalloc_request_page(void);
void mem_pgalloc_lock_page(void *page);
void mem_pgalloc_unlock_page(void *page);

#endif
