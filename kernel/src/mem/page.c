#include "mem/page.h"

#include <stdbool.h>
#include <stdint.h>
#include "mem/pgalloc.h"

#define MAX_TABLE_ENTRIES 512

struct page_index {
        int pdpt;
        int pdt;
        int pt;
        int page;
};

/* structure is also used for pdpt entry and pml4 entry */
struct page_dir_entry {
        bool present : 1;
        bool read_write : 1;
        bool user_super : 1;
        bool write_through : 1;
        bool disable_caching : 1;
        bool accessed : 1;
        bool available_0 : 1;
        bool large_pages : 1;
        uint8_t available_1 : 4;
        uint64_t addr : 52;
};

/* structure is also used for pdpt and pml4 */
struct page_dir {
        struct page_dir_entry entries[MAX_TABLE_ENTRIES];
};

static struct page_dir *pml4;
static size_t page_size;

void mem_page_init(size_t _page_size)
{
        static bool initialized = false;

        if (initialized)
                return;

        page_size = _page_size;
        pml4 = mem_pgalloc_request_zero_page();

        /* identity map 512mb */
        mem_page_map_pages((void *)0x0, (void *)0x0, 0x20000000 / page_size);

        initialized = true;
}

struct page_table_entry {
        bool present : 1;
        bool read_write : 1;
        bool user_super : 1;
        bool write_through : 1;
        bool disable_caching : 1;
        bool accessed : 1;
        bool dirty : 1;
        bool page_attr_table : 1;
        bool global : 1;
        uint8_t available : 3;
        uint64_t addr : 52;
};

struct page_table {
        struct page_table_entry entries[MAX_TABLE_ENTRIES];
};

/* new paging data structures are created when necessary */
void mem_page_map_page(void *phys_addr, void *virt_addr)
{
        struct page_index ind = {
                .page = (uintptr_t)virt_addr >> 12 & 0x1ff,
                .pt = (uintptr_t)virt_addr >> 21 & 0x1ff,
                .pdt = (uintptr_t)virt_addr >> 30 & 0x1ff,
                .pdpt = (uintptr_t)virt_addr >> 39 & 0x1ff,
        };

        struct page_dir_entry *ent = &pml4->entries[ind.pdpt];

        struct page_dir *pdpt;

        if (!ent->present) {
                pdpt = mem_pgalloc_request_zero_page();
                *ent = (struct page_dir_entry){
                        .addr = (uintptr_t)pdpt >> 12,
                        .present = true,
                        .read_write = true,
                };
        } else
                pdpt = (struct page_dir *)(uintptr_t)(ent->addr << 12);

        ent = &pdpt->entries[ind.pdt];

        struct page_dir *pdt;

        if (!ent->present) {
                pdt = mem_pgalloc_request_zero_page();
                *ent = (struct page_dir_entry){
                        .addr = (uintptr_t)pdt >> 12,
                        .present = true,
                        .read_write = true,
                };
        } else
                pdt = (struct page_dir *)(uintptr_t)(ent->addr << 12);
        
        ent = &pdt->entries[ind.pt];

        struct page_table *pt;

        if (!ent->present) {
                pt = mem_pgalloc_request_zero_page();
                *ent = (struct page_dir_entry){
                        .addr = (uintptr_t)pt >> 12,
                        .present = true,
                        .read_write = true,
                };
        } else
                pt = (struct page_table *)(uintptr_t)(ent->addr << 12);

        pt->entries[ind.page] = (struct page_table_entry){
                .addr = (uintptr_t)phys_addr >> 12,
                .present = true,
                .read_write = true,
        };
}

void mem_page_map_pages(void *phys_addr, void *virt_addr, size_t page_cnt)
{
        for (size_t i = 0; i < page_cnt; ++i) {
                mem_page_map_page((void *)((uintptr_t)phys_addr + i * page_size),
                                  (void *)((uintptr_t)virt_addr + i * page_size));
        }
}
