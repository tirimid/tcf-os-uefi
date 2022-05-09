#include "kern.h"

#include <stdbool.h>
#include "io.h"

void kern_ctl_init_kernel(const struct com_boot_boot_info *info)
{
        io_gfx_init_gfx(&info->frame_buf);
        io_gfx_init_psf(&info->font);
}

void kern_ctl_hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
