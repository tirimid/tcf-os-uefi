#include "kern/kern.h"

#include "mem/pgalloc.h"
#include "int/pic.h"
#include <stdbool.h>
#include "io/gfx.h"
#include "int/idt.h"
#include "cpu/gdt.h"
#include "mem/paging.h"
#include "mem/heap.h"
#include "sched/pit.h"

void kern_init(const struct boot_info *info)
{
        static bool initialized = false;

        if (initialized)
                return;
        
        gfx_init(&info->frame_buf, &info->font);
        
        gdt_init();
        
        pgalloc_init(&info->mem_map, info->page_size);

        pgalloc_reserve_pages(info->frame_buf.base, info->frame_buf.size / info->page_size + 1);

        paging_init(info->page_size);
        heap_init(200, info->page_size);
        
        idt_init();
        pic_remap(0x20, 0x28);
        pic_mask(0xfc, 0xff);

        pit_init(500);
        
        initialized = true;
}

void kern_hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
