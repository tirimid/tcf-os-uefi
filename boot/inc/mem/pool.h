#ifndef BOOT_MEM_POOL_H
#define BOOT_MEM_POOL_H

#include <stddef.h>

void *mem_pool_alloc_mem(size_t size);
void mem_pool_free_mem(void *buf);

#endif
