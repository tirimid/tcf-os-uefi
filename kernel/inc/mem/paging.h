#ifndef _MEM_PAGING_H_
#define _MEM_PAGING_H_

#include <stdint.h>
#include <stddef.h>

void paging_init(size_t _page_size);

/* new paging data structures are created when necessary */
void paging_map_page(void *phys_addr, void *virt_addr);
void paging_map_pages(void *phys_addr, void *virt_addr, size_t page_cnt);

#endif
