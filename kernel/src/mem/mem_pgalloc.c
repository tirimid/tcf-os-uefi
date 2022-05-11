#include "mem.h"

#include <stdbool.h>
#include "util.h"

static struct util_ds_bitmap page_bm;
static int page_size;

void mem_pgalloc_init(const struct com_mem_map *mem_map, int _page_size)
{
        static bool initialized = false;

        if (initialized)
                return;

        page_size = _page_size;

        initialized = true;
}

void *mem_pgalloc_request_page(void)
{
}

void mem_pgalloc_lock_page(void *page)
{
}

void mem_pgalloc_unlock_page(void *page)
{
}
