#ifndef KERNEL_MEM_HEAP_H
#define KERNEL_MEM_HEAP_H

#include <stdint.h>
#include <stddef.h>

void mem_heap_init(void);

void *mem_heap_alloc(size_t size);
void mem_heap_free(void *ptr);

#endif
