#ifndef POOL_H_GsreGJEfyGuSMNzxdEsah939iDG3BiZi
#define POOL_H_GsreGJEfyGuSMNzxdEsah939iDG3BiZi

#include <stddef.h>

void *
alloc_pool_mem(size_t size);

void
free_pool_mem(void *buf);

#endif
