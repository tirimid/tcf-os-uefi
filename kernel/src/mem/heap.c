#include "mem/heap.h"

#include <stdbool.h>
#include "mem/pgalloc.h"
#include <stddef.h>

struct heap_header {
        struct heap_header *next;
        size_t size;
};

static struct heap_header *heap_ptr;
static struct heap_header *last_hdr;
static size_t heap_pages;

void mem_heap_init(size_t _heap_pages)
{
        static bool initialized = false;

        if (initialized)
                return;

        heap_pages = _heap_pages;
        heap_ptr = mem_pgalloc_request_pages(heap_pages);
        *heap_ptr = (struct heap_header){
                .next = NULL,
                .size = 0,
        };
        last_hdr = heap_ptr;

        initialized = true;
}

void *mem_heap_alloc(size_t size)
{
}

void mem_heap_free(void *ptr)
{
}
