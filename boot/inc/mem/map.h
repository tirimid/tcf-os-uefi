#ifndef BOOT_MEM_MAP_H
#define BOOT_MEM_MAP_H

#include "commem.h"

/* resources of returned map must be freed */
struct com_mem_map mem_map_get(void);

#endif
