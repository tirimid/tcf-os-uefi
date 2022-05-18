#ifndef MEM_HEAP_H__
#define MEM_HEAP_H__

#include <stdint.h>
#include <stddef.h>

void heap_init(size_t _heap_pages, size_t _page_size);

void *heap_alloc(size_t size);
void heap_free(void *ptr);
void *heap_realloc(void *ptr, size_t new_size);

#endif
