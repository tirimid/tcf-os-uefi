#include "mem/pgalloc.h"

#include <stdbool.h>
#include "util/ds.h"
#include <stdint.h>
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

void *mem_pgalloc_request_pages(size_t page_cnt)
{
        for (size_t i = bitmap_ind_start; i < page_bm.size_bits; ++i) {
                if (util_ds_bitmap_bit(&page_bm, i))
                        continue;

                size_t free_pages = 0;

                for (; free_pages <= page_cnt; ++free_pages) {
                        if (util_ds_bitmap_bit(&page_bm, i + free_pages))
                                break;
                }

                if (free_pages > page_cnt) {
                        void *page = (void *)(i * page_size);
                        bitmap_ind_start = i + free_pages;

                        mem_pgalloc_lock_pages(page, free_pages);

                        return page;
                }
        }

        return NULL;
}

void mem_pgalloc_free_page(void *page)
{
        mem_pgalloc_unlock_page(page);

        bitmap_ind_start = (uintptr_t)page / page_size;
}

void mem_pgalloc_lock_page(void *page)
{
        util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size, true);
}

void mem_pgalloc_lock_pages(void *page, size_t page_cnt)
{
        for (int i = 0; i < page_cnt; ++i)
                util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size + i, true);
}

void mem_pgalloc_unlock_page(void *page)
{
        util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size, false);
}

void mem_pgalloc_unlock_pages(void *page, size_t page_cnt)
{
        for (int i = 0; i < page_cnt; ++i)
                util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size + i, false);
}
