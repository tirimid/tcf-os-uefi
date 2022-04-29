#include "kernel.h"

#include <stdbool.h>
#include "io/gfx.h"

void
init_kernel(const struct boot_info *info)
{
        init_gfx(&info->frame_buf);
}

void
hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
