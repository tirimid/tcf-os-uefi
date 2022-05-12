#include "mem.h"

#include <stdbool.h>

void mem_heap_init(void)
{
        static bool initialized = false;

        if (initialized)
                return;

        initialized = true;
}

void *mem_heap_alloc(size_t size)
{
}

void mem_heap_free(void *ptr)
{
}
