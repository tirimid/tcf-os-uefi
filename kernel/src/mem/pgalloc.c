#include "mem/pgalloc.h"

#include <stdbool.h>

static int page_size;

void init_page_alloc(int _page_size)
{
        page_size = _page_size;
}
