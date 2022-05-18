#ifndef MEM_MMAP_H__
#define MEM_MMAP_H__

#include "common/mem.h"

/* resources of returned map must be freed */
struct mem_map mmap_get(void);

#endif
