#include "kern.h"

#include "mem.h"
#include <stdbool.h>
#include "io.h"
#include "int.h"
#include "cpu.h"

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

        initialized = true;
}

void kern_ctl_hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
