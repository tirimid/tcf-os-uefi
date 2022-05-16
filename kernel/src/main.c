#include "kern/ctl.h"
#include "comboot.h"
#include "io/gfx.h"
#include <stddef.h>
#include "mem/heap.h"
#include "mem/pgalloc.h"
#include "sched/pit.h"
#include <stdbool.h>

__attribute__((ms_abi)) int main(const struct com_boot_info *info)
{
        kern_ctl_init(info);

        io_gfx_clear_screen(IO_GFX_COLOR_BLACK);
        io_gfx_draw_psf_string(0, 0, "hello world", IO_GFX_COLOR_WHITE);

        for (int i = 0; i < 90; ++i) {
                io_gfx_draw_psf_glyph(8 * i, 96, 's', IO_GFX_COLOR_GREEN);
                sched_pit_sleep(50);
        }

        while (true)
                __asm__("hlt\n");

        return 0;
}
