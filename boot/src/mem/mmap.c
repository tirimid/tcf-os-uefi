#include "mem/mmap.h"

#include <efi.h>
#include <efilib.h>
#include <stdint.h>
#include "mem/pool.h"
#include <stddef.h>

/* resources of returned map must be freed */
struct mem_map mmap_get(void)
{
        struct mem_map map = { 0 };

        size_t size;
        uint64_t key;
        uint32_t desc_ver;

        BS->GetMemoryMap(&size, (EFI_MEMORY_DESCRIPTOR *)map.map, &key, &map.ent_size, &desc_ver);
        map.map = pool_alloc(size);
        BS->GetMemoryMap(&size, (EFI_MEMORY_DESCRIPTOR *)map.map, &key, &map.ent_size, &desc_ver);

        map.entries = size / map.ent_size;

        return map;
}
