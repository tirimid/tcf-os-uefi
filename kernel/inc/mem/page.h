#ifndef KERNEL_MEM_PAGE_H
#define KERNEL_MEM_PAGE_H

#include <stdint.h>
#include <stddef.h>

void mem_page_init(void);

void mem_page_map_page(void *phys_addr, void *virt_addr);
void mem_page_map_pages(void *phys_addr, void *virt_addr, size_t page_cnt);

#endif
