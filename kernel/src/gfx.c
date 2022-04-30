#include "gfx.h"

#include "string.h"
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
draw_hollow_box(int x, int y, int w, int h, struct color col)
{
        for (int i = x; i < x + w; ++i) {
                for (int j = y; j < y + h; ++j) {
                        bool should_draw = i == x || i == x + w - 1 || j == y
                                           || j == y + h - 1;

                        if (should_draw)
                                draw_pixel(i, j, col);
                }
        }
}

void
clear_screen(struct color col)
{
        uint64_t q = *(const uint64_t *)&col << 32 | *(const uint64_t *)&col;
        size_t writes = frame_buf.res_horiz * frame_buf.res_vert / 2;

        fast_memset(frame_buf.base, q, writes);
}

static struct psf_font psf_font;

void
init_psf(const struct psf_font *font_in_use)
{
        psf_font = *font_in_use;
}

void
draw_psf_glyph(int x, int y, wchar_t c, struct color col)
{
        const uint8_t *glyph
                = &psf_font.glyph_buf[c * psf_font.hdr.glyph_bytes];

        for (int j = 0; j < psf_font.hdr.height; ++j) {
                for (int i = 0; i < psf_font.hdr.width; ++i) {
                        int glyph_byte = j * psf_font.hdr.width / 8;
                        uint8_t bitmask = 1 << 7 >> i % 8;

                        if ((glyph[glyph_byte] & bitmask) > 0)
                                draw_pixel(x + i, y + j, col);
                }
        }
}
