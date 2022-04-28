#include "kernel.h"
#include "boottypes.h"
#include <stdint.h>

static inline uint32_t
true_color(uint8_t r, uint8_t g, uint8_t b)
{
        return (uint32_t)r << 16 | (uint32_t)g << 8 | b;
}

static struct boot_info boot_info;

static inline void
clear_screen(uint32_t true_col)
{
        uint32_t *fb_base = boot_info.frame_buf.base;
        for (int i = 0; i < boot_info.frame_buf.res_vert; ++i) {
                for (int j = 0; j < boot_info.frame_buf.res_horiz; ++j) {
                        uint32_t *dst = fb_base + i
                                        * boot_info.frame_buf.res_horiz + j;
                        *dst = true_col;
                }
        }
}

__attribute__((ms_abi)) int
kernel_main(const struct boot_info *info)
{
        boot_info = *info;
        clear_screen(true_color(0, 0, 100));
        hang();
        return 0;
}
