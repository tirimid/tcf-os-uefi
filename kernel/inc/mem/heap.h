#ifndef KERNEL_MEM_HEAP_H
#define KERNEL_MEM_HEAP_H

#include <stdint.h>
#include <stddef.h>

void mem_heap_init(size_t _heap_pages, size_t _page_size);

void *mem_heap_alloc(size_t size);
void mem_heap_free(void *ptr);
void *mem_heap_realloc(void *ptr, size_t new_size);

#endif
