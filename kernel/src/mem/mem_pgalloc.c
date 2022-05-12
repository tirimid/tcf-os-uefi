#include "mem.h"

#include <stdbool.h>
#include "util.h"
#include "lcstring.h"

static struct util_ds_bitmap page_bm;
static size_t page_size;

void mem_pgalloc_init(struct com_mem_map *mem_map, size_t _page_size)
{
        static bool initialized = false;

        if (initialized)
                return;

        page_size = _page_size;

        struct com_mem_map_entry *largest_free_ent = mem_map->map;

        for (int i = 0; i < mem_map->entries; ++i) {
                uintptr_t ent_addr = (uintptr_t)mem_map->map + mem_map->ent_size * i;
                struct com_mem_map_entry *ent = (struct com_mem_map_entry *)ent_addr;

                bool larger = ent->type == COM_MEM_MAP_ENTRY_TYPE_CONVENTIONAL
                              && ent->page_cnt > largest_free_ent->page_cnt;

                if (larger)
                        largest_free_ent = ent;
        }

        page_bm = (struct util_ds_bitmap){
                .data = (uint8_t *)largest_free_ent,
                .size_bits = largest_free_ent->page_cnt,
        };

        memset(page_bm.data, 0, util_ds_bitmap_size_bytes(&page_bm));

        initialized = true;
}

void *mem_pgalloc_request_page(void)
{
        return mem_pgalloc_request_pages(1);
}

static size_t bitmap_ind_start = 0;

void *mem_pgalloc_request_pages(int page_cnt)
{
}

static inline size_t page_to_bitmap_ind(const void *page)
{
        return (uintptr_t)page / page_size;
}

void mem_pgalloc_lock_page(void *page)
{
        util_ds_set_bitmap_bit(&page_bm, page_to_bitmap_ind(page), true);
}

void mem_pgalloc_lock_pages(void *page, int page_cnt)
{
        for (int i = 0; i < page_cnt; ++i)
                util_ds_set_bitmap_bit(&page_bm, page_to_bitmap_ind(page) + i, true);
}

void mem_pgalloc_unlock_page(void *page)
{
        util_ds_set_bitmap_bit(&page_bm, page_to_bitmap_ind(page), false);
}

void mem_pgalloc_unlock_pages(void *page, int page_cnt)
{
        for (int i = 0; i < page_cnt; ++i)
                util_ds_set_bitmap_bit(&page_bm, page_to_bitmap_ind(page) + i, false);
}
