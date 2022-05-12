#ifndef COMMON_COMMEM_H
#define COMMON_COMMEM_H

#include <stdint.h>
#include <stddef.h>

enum com_mem_map_entry_type {
        COM_MEM_MAP_ENTRY_TYPE_RESERVED = 0,
        COM_MEM_MAP_ENTRY_TYPE_LOADER_CODE = 1,
        COM_MEM_MAP_ENTRY_TYPE_LOADER_DATA = 2,
        COM_MEM_MAP_ENTRY_TYPE_BOOT_SVC_CODE = 3,
        COM_MEM_MAP_ENTRY_TYPE_BOOT_SVC_DATA = 4,
        COM_MEM_MAP_ENTRY_TYPE_RUNTIME_SVC_CODE = 5,
        COM_MEM_MAP_ENTRY_TYPE_RUNTIME_SVC_DATA = 6,
        COM_MEM_MAP_ENTRY_TYPE_CONVENTIONAL = 7,
        COM_MEM_MAP_ENTRY_TYPE_UNUSABLE = 8,
        COM_MEM_MAP_ENTRY_TYPE_ACPI_RECLAIMABLE = 9,
        COM_MEM_MAP_ENTRY_TYPE_ACPI_NVS = 10,
        COM_MEM_MAP_ENTRY_TYPE_MAPPED_IO = 11,
        COM_MEM_MAP_ENTRY_TYPE_MAPPED_IO_PORT_SPACE = 12,
        COM_MEM_MAP_ENTRY_TYPE_PAL_CODE = 13,
};

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
