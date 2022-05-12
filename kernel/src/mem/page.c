#include "mem/page.h"

#include <stdbool.h>

void mem_page_init(void)
{
        static bool initialized = false;

        if (initialized)
                return;

        initialized = true;
}

void mem_page_map(void *phys_addr, void *virt_addr)
{
}

void mem_page_map_pages(void *phys_addr, void *virt_addr, size_t page_cnt)
{
}
