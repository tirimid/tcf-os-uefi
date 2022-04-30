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
                        if (i == x || i == x + w || j == y || j == y + h)
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

static inline bool
is_psf_glyph_masked(const uint8_t *glyph, int i, int j)
{
        int byte = j * psf_font.hdr.width / 8;
        uint8_t mask = 1 << 7 >> i % 8;
        return (glyph[byte] & mask) > 0;
}

void
draw_psf_glyph(int x, int y, wchar_t c, struct color col)
{
        const uint8_t *glyph
                = &psf_font.glyph_buf[c * psf_font.hdr.glyph_bytes];
        for (int j = 0; j < psf_font.hdr.height; ++j) {
                for (int i = 0; i < psf_font.hdr.width; ++i) {
                        if (is_psf_glyph_masked(glyph, i , j))
                                draw_pixel(x + i, y + j, col);
                }
        }
}
