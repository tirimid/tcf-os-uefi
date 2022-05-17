#include "mem/pgalloc.h"

#include <stdbool.h>
#include "util/ds.h"
#include <stdint.h>
#include "lcstring.h"
#include "kern/error.h"

static struct util_ds_bitmap page_bm;
static size_t page_size;

void mem_pgalloc_init(const struct com_mem_map *mem_map, size_t _page_size)
{
        static bool initialized = false;

        if (initialized)
                return;

        page_size = _page_size;

        const struct com_mem_map_entry *largest_free_ent = mem_map->map;
        size_t total_page_cnt = 0;

        for (int i = 0; i < mem_map->entries; ++i) {
                uintptr_t ent_addr = (uintptr_t)mem_map->map + mem_map->ent_size * i;
                const struct com_mem_map_entry *ent = (const struct com_mem_map_entry *)ent_addr;

                bool larger = ent->type == COM_MEM_MAP_ENTRY_TYPE_CONVENTIONAL
                              && ent->page_cnt > largest_free_ent->page_cnt;

                if (larger)
                        largest_free_ent = ent;

                total_page_cnt += ent->page_cnt;
        }

        page_bm = (struct util_ds_bitmap){
                .data = largest_free_ent->phys_start,
                .size_bits = total_page_cnt,
        };

        size_t bm_data_page_cnt = util_ds_bitmap_size_bytes(&page_bm) / page_size + 1;

        if (bm_data_page_cnt > largest_free_ent->page_cnt) {
                kern_error_panic(KERN_ERROR_PANIC_CODE_VITAL_INIT_FAIL,
                                 "not enough space for page bitmap");
        }

        mem_pgalloc_reserve_pages(page_bm.data, bm_data_page_cnt);
        memset(page_bm.data, 0, util_ds_bitmap_size_bytes(&page_bm));
        
        mem_pgalloc_reserve_pages((void *)0x0, 256);

        initialized = true;
}

static size_t bitmap_ind_start = 0;

void *mem_pgalloc_request_page(void)
{
        for (size_t i = bitmap_ind_start; i < page_bm.size_bits; ++i) {
                if (util_ds_bitmap_bit(&page_bm, i))
                        continue;

                bitmap_ind_start = i + 1;

                void *page = (void *)(i * page_size);
                
                mem_pgalloc_reserve_page(page);

                return page;
        }

        return NULL;
}

static size_t free_pages_at_bit(size_t bit, size_t max_pages)
{
        size_t pages = 0;

        for (size_t i = bit; i < page_bm.size_bits && i <= bit + max_pages; ++i) {
                if (!util_ds_bitmap_bit(&page_bm, i))
                        ++pages;
                else
                        break;
        }

        return pages;
}

void *mem_pgalloc_request_pages(size_t page_cnt)
{
        for (size_t i = bitmap_ind_start; i < page_bm.size_bits; ++i) {
                if (util_ds_bitmap_bit(&page_bm, i))
                        continue;

                size_t free_pages = free_pages_at_bit(i, page_cnt);

                if (free_pages >= page_cnt) {
                        bitmap_ind_start = i + free_pages;
                        
                        void *page = (void *)(i * page_size);

                        mem_pgalloc_reserve_pages(page, free_pages);

                        return page;
                } else
                        i += free_pages;
        }

        return NULL;
}

void *mem_pgalloc_request_zero_page(void)
{
        void *page = mem_pgalloc_request_page();

        if (page == NULL)
                return NULL;

        fast_memset(page, 0, page_size / 8);

        return page;
}

void *mem_pgalloc_request_zero_pages(size_t page_cnt)
{
        void *pages = mem_pgalloc_request_pages(page_cnt);
        
        if (pages == NULL)
                return NULL;
        
        fast_memset(pages, 0, page_cnt * page_size / 8);

        return pages;
}

void mem_pgalloc_reserve_page(void *page)
{
        util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size, true);
}

void mem_pgalloc_reserve_pages(void *page, size_t page_cnt)
{
        for (size_t i = 0; i < page_cnt; ++i)
                util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size + i, true);
}

void mem_pgalloc_free_page(void *page)
{
        util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size, false);

        size_t new_bis = (uintptr_t)page / page_size;

        if (new_bis < bitmap_ind_start)
                bitmap_ind_start = new_bis;
}

void mem_pgalloc_free_pages(void *page, size_t page_cnt)
{
        for (size_t i = 0; i < page_cnt; ++i)
                util_ds_set_bitmap_bit(&page_bm, (uintptr_t)page / page_size + i, false);

        size_t new_bis = (uintptr_t)page / page_size;

        if (new_bis < bitmap_ind_start)
                bitmap_ind_start = new_bis;
}
