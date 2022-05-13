#include "kern/ctl.h"

#include "mem/pgalloc.h"
#include "int/pic.h"
#include <stdbool.h>
#include "io/gfx.h"
#include "int/idt.h"
#include "cpu/gdt.h"
#include "mem/page.h"
#include "mem/heap.h"

void kern_ctl_init(struct com_boot_info *info)
{
        static bool initialized = false;

        if (initialized)
                return;

        io_gfx_init(&info->frame_buf, &info->font);
        
        cpu_gdt_init();

        int_pic_remap(0x20, 0x28);
        int_idt_init();
        
        mem_pgalloc_init(&info->mem_map, info->page_size);
        mem_page_init(info->page_size);
        mem_heap_init(200);

        initialized = true;
}

void kern_ctl_hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
