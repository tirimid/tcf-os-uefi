#ifndef MEM_POOL_H__
#define MEM_POOL_H__

#include <stddef.h>

void *pool_alloc(size_t size);
void pool_free(void *buf);

#endif
