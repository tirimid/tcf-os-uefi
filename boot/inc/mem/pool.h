#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#include <stddef.h>

void *pool_alloc(size_t size);
void pool_free(void *buf);

#endif
