#include "kern.h"

#include <stdbool.h>
#include "io.h"
#include "int.h"
#include "cpu.h"

void kern_ctl_init_kernel(const struct com_boot_boot_info *info)
{
        io_gfx_init_gfx(&info->frame_buf);
        io_gfx_init_psf(&info->font);
        cpu_gdt_init_gdt();
        int_idt_init_idt();
}

void kern_ctl_hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
