#include "kern/kern.h"
#include "common/boot.h"
#include "io/gfx.h"
#include <stddef.h>
#include "mem/heap.h"
#include "mem/pgalloc.h"
#include "sched/pit.h"
#include <stdbool.h>

__attribute__((ms_abi)) int main(const struct boot_info *info)
{
        kern_init(info);

        gfx_clear_screen(GFX_COLOR_BLACK);
        gfx_draw_psf_string(0, 0, "hello world", GFX_COLOR_WHITE);

        for (int i = 0; i < 90; ++i) {
                gfx_draw_psf_glyph(8 * i, 96, 's', GFX_COLOR_GREEN);
                pit_sleep(50);
        }

        while (true)
                __asm__("hlt\n");

        return 0;
}
