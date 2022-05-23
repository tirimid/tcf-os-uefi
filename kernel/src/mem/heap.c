#include "mem/heap.h"

#include <stdbool.h>
#include "mem/pgalloc.h"
#include <stddef.h>
#include "lcstring.h"

struct heap_header {
        struct heap_header *next;
        size_t size;
};

static struct heap_header *heap_ptr;
static struct heap_header *last_hdr;

static size_t heap_pages;
static size_t page_size;

void heap_init(size_t _heap_pages, size_t _page_size)
{
        static bool initialized = false;

        if (initialized)
                return;

        heap_pages = _heap_pages;
        page_size = _page_size;
        
        heap_ptr = pgalloc_request_pages(heap_pages);
        *heap_ptr = (struct heap_header){
                .next = NULL,
                .size = 0,
        };
        last_hdr = heap_ptr;

        initialized = true;
}

static bool is_region_free(const void *ptr, size_t size)
{
        for (const struct heap_header *hdr = heap_ptr; hdr != NULL; hdr = hdr->next) {
                if ((uintptr_t)ptr <= (uintptr_t)hdr + sizeof(*hdr) + hdr->size
                    && (uintptr_t)ptr + size >= (uintptr_t)hdr) {
                        return false;
                }
        }

        return true;
}

void *heap_alloc(size_t size)
{
        void *alloc_reg = NULL;
        size_t total_size = size + sizeof(struct heap_header);

        for (struct heap_header *hdr = heap_ptr; hdr != NULL; hdr = hdr->next) {
                uintptr_t pot_free_addr = (uintptr_t)hdr + sizeof(*hdr) + hdr->size + 1;

                if (is_region_free((const void *)pot_free_addr, total_size)) {
                        alloc_reg = (void *)pot_free_addr;

                        break;
                }
        }

        uintptr_t heap_end_addr = (uintptr_t)heap_ptr + heap_pages * page_size;

        if (alloc_reg == NULL || (uintptr_t)alloc_reg + total_size >= heap_end_addr)
                return NULL;

        *(struct heap_header *)alloc_reg = (struct heap_header){
                .next = NULL,
                .size = size,
        };
        last_hdr->next = alloc_reg;
        last_hdr = alloc_reg;

        return (void *)((uintptr_t)alloc_reg + sizeof(struct heap_header));
}

void heap_free(void *ptr)
{
        struct heap_header *prev_hdr = NULL;

        for (struct heap_header *hdr = heap_ptr; hdr->next != NULL; hdr = hdr->next) {
                size_t size = sizeof(*hdr->next) + hdr->next->size;
                
                if ((uintptr_t)ptr <= (uintptr_t)hdr->next + size
                    && (uintptr_t)ptr >= (uintptr_t)hdr->next) {
                        prev_hdr = hdr;
                        
                        break;
                }
        }

        if (prev_hdr == NULL)
                return;

        if (prev_hdr->next == last_hdr)
                last_hdr = prev_hdr;

        prev_hdr->next = prev_hdr->next->next;
}

void *heap_realloc(void *ptr, size_t new_size)
{
        struct heap_header *alloc_hdr = NULL;

        for (struct heap_header *hdr = heap_ptr; hdr != NULL; hdr = hdr->next) {
                bool collision = (uintptr_t)ptr <= (uintptr_t)hdr + sizeof(*hdr) + hdr->size
                                 && (uintptr_t)ptr >= (uintptr_t)hdr;

                if (collision) {
                        alloc_hdr = hdr;

                        break;
                }
        }

        if (alloc_hdr == NULL || new_size < alloc_hdr->size)
                return NULL;

        void *new_ptr = heap_alloc(new_size);

        if (new_ptr == NULL)
                return NULL;

        memcpy(new_ptr, alloc_hdr + 1, alloc_hdr->size);
        heap_free(ptr);

        return new_ptr;
}
