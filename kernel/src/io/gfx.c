#include "io/gfx.h"

#include "libc/string.h"
#include <stddef.h>

static struct frame_buf frame_buf;

void
init_gfx(const struct frame_buf *fb_in_use)
{
        frame_buf = *fb_in_use;
}

void
draw_pixel(int x, int y, struct color col)
{
        struct color *dst = (struct color *)frame_buf.base
                            + frame_buf.scanline_pixels * y + x;
        col._ignore = 255;
        *dst = col;
}

void
draw_box(int x, int y, int w, int h, struct color col)
{
        for (int i = x; i < x + w; ++i) {
                for (int j = y; j < y + h; ++j)
                        draw_pixel(i, j, col);
        }
}

void
clear_screen(struct color col)
{
        uint64_t q = *(const uint64_t *)&col << 32 | *(const uint64_t *)&col;
        size_t writes = frame_buf.res_horiz * frame_buf.res_vert / 2;
        fast_memset(frame_buf.base, q, writes);
}
