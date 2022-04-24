#ifndef POOL_H_t7veJkvAVq3pe3wjoiIowePAKUoh3KWx
#define POOL_H_t7veJkvAVq3pe3wjoiIowePAKUoh3KWx

#include <stddef.h>

void *
alloc_pool_mem(size_t size);

void
free_pool_mem(void *buf);

#endif
