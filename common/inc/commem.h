#ifndef COMMON_COMMEM_H
#define COMMON_COMMEM_H

#include <stdint.h>
#include <stddef.h>

struct com_mem_map_entry {
        uint32_t type;
        void *phys_start;
        void *virt_start;
        uint64_t page_cnt;
        uint64_t attr;
};

struct com_mem_map {
        struct com_mem_map_entry *map;
        size_t ent_size;
        int entries;
};

#endif
