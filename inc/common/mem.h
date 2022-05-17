#ifndef _COMMON_MEM_H_
#define _COMMON_MEM_H_

#include <stdint.h>
#include <stddef.h>

enum mem_map_entry_type {
        MEM_MAP_ENTRY_TYPE_RESERVED = 0,
        MEM_MAP_ENTRY_TYPE_LOADER_CODE = 1,
        MEM_MAP_ENTRY_TYPE_LOADER_DATA = 2,
        MEM_MAP_ENTRY_TYPE_BOOT_SVC_CODE = 3,
        MEM_MAP_ENTRY_TYPE_BOOT_SVC_DATA = 4,
        MEM_MAP_ENTRY_TYPE_RUNTIME_SVC_CODE = 5,
        MEM_MAP_ENTRY_TYPE_RUNTIME_SVC_DATA = 6,
        MEM_MAP_ENTRY_TYPE_CONVENTIONAL = 7,
        MEM_MAP_ENTRY_TYPE_UNUSABLE = 8,
        MEM_MAP_ENTRY_TYPE_ACPI_RECLAIMABLE = 9,
        MEM_MAP_ENTRY_TYPE_ACPI_NVS = 10,
        MEM_MAP_ENTRY_TYPE_MAPPED_IO = 11,
        MEM_MAP_ENTRY_TYPE_MAPPED_IO_PORT_SPACE = 12,
        MEM_MAP_ENTRY_TYPE_PAL_CODE = 13,
};

struct mem_map_entry {
        uint32_t type;
        void *phys_start;
        void *virt_start;
        uint64_t page_cnt;
        uint64_t attr;
};

struct mem_map {
        struct mem_map_entry *map;
        size_t ent_size;
        int entries;
};

#endif
