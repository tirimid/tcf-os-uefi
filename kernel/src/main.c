#include "kernel.h"
#include "boottypes.h"
#include <stdint.h>

static struct boot_info boot_info;

static inline void
set_pixel(int x, int y, uint32_t color)
{
        uint32_t *dst = (uint32_t *)boot_info.frame_buf.base + 4
                        * boot_info.frame_buf.scanline_pixels * y + 4 * x;
        *dst = color;
}

int
kernel_main(const struct boot_info *info)
{
        boot_info = *info;
        set_pixel(40, 200, 0xffffffff);
        hang();
        return 0;
}
