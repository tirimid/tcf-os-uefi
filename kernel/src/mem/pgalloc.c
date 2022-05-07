#include "mem/pgalloc.h"

#include <stdbool.h>

static int page_size;

void
init_page_alloc(int _page_size)
{
        static bool initialized = false;

        if (initialized)
                return;

        page_size = _page_size;
        initialized = true;
}
