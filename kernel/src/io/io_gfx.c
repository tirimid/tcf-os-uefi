#include "io.h"

#include "lcstring.h"

static struct com_gfx_frame_buf frame_buf;

void io_gfx_init_gfx(const struct com_gfx_frame_buf *_frame_buf)
{
        frame_buf = *_frame_buf;
}

void io_gfx_draw_pixel(int x, int y, struct io_gfx_color col)
{
        struct io_gfx_color *dst = (struct io_gfx_color *)frame_buf.base
                                   + frame_buf.scanline_pixels * y + x;

        col._ignore = 255;
        *dst = col;
}

void io_gfx_draw_rect(const struct io_gfx_rect *rect, struct io_gfx_color col)
{
        for (int i = rect->x; i < rect->x + rect->w; ++i) {
                for (int j = rect->y; j < rect->y + rect->h; ++j) {
                        bool should_draw = i == rect->x
                                           || i == rect->x + rect->w - 1
                                           || j == rect->y
                                           || j == rect->y + rect->h - 1;

                        if (should_draw)
                                io_gfx_draw_pixel(i, j, col);
                }
        }
}

void io_gfx_fill_rect(const struct io_gfx_rect *rect, struct io_gfx_color col)
{
        for (int i = rect->x; i < rect->x + rect->w; ++i) {
                for (int j = rect->y; j < rect->y + rect->h; ++j)
                        io_gfx_draw_pixel(i, j, col);
        }
}

void io_gfx_clear_screen(struct io_gfx_color col)
{
        uint64_t q = *(const uint64_t *)&col << 32 | *(const uint64_t *)&col;
        size_t writes = frame_buf.res_horiz * frame_buf.res_vert / 2;

        fast_memset(frame_buf.base, q, writes);
}

static struct com_gfx_psf_font psf_font;

void io_gfx_init_psf(const struct com_gfx_psf_font *_psf_font)
{
        psf_font = *_psf_font;
}

void io_gfx_draw_psf_glyph(int x, int y, wchar_t c, struct io_gfx_color col)
{
        int glyph_ind = c * psf_font.hdr.glyph_bytes;
        const uint8_t *glyph = &psf_font.glyph_buf[glyph_ind];

        for (int j = 0; j < psf_font.hdr.height; ++j) {
                for (int i = 0; i < psf_font.hdr.width; ++i) {
                        int glyph_byte = j * psf_font.hdr.width / 8;
                        uint8_t bitmask = 1 << 7 >> i % 8;

                        if ((glyph[glyph_byte] & bitmask) > 0)
                                io_gfx_draw_pixel(x + i, y + j, col);
                }
        }
}
