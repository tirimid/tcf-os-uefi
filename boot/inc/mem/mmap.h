#ifndef _MEM_MMAP_H_
#define _MEM_MMAP_H_

#include "common/mem.h"

/* resources of returned map must be freed */
struct mem_map mmap_get(void);

#endif
