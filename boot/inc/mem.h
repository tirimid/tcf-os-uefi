#ifndef MEM_H_l3UOvtqPXbTmzk1XLtVTO642pK4wbFKu
#define MEM_H_l3UOvtqPXbTmzk1XLtVTO642pK4wbFKu

#include <stddef.h>

#define PAGE_SIZE EFI_PAGE_SIZE

/* ==========
 * mem_pool.c
 * ==========
 */

void *mem_pool_alloc_mem(size_t size);
void mem_pool_free_mem(void *buf);

/* ==========
 * mem_page.c
 * ==========
 */

void *mem_page_alloc_page(void *phys_addr);
void *mem_page_alloc_pages(void *phys_addr, size_t cnt);

#endif
