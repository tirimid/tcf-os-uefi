#include "io/gfx.h"

#include <stdbool.h>
#include "lcstring.h"

static struct gfx_frame_buf frame_buf;
static struct gfx_psf_font psf_font;

void gfx_init(const struct gfx_frame_buf *_frame_buf, const struct gfx_psf_font *_psf_font)
{
        static bool initialized = false;

        if (initialized)
                return;

        frame_buf = *_frame_buf;
        psf_font = *_psf_font;

        initialized = true;
}

void gfx_draw_pixel(int x, int y, struct gfx_color col)
{
        struct gfx_color *dst = (struct gfx_color *)frame_buf.base
                                + frame_buf.scanline_pixels * y + x;

        col._ignore = 255;
        *dst = col;
}

void gfx_draw_rect(const struct gfx_rect *rect, struct gfx_color col)
{
        for (int i = rect->x; i < rect->x + rect->w; ++i) {
                for (int j = rect->y; j < rect->y + rect->h; ++j)
                        gfx_draw_pixel(i, j, col);
        }
}

void gfx_draw_hollow_rect(const struct gfx_rect *rect, struct gfx_color col)
{
        for (int i = rect->x; i < rect->x + rect->w; ++i) {
                for (int j = rect->y; j < rect->y + rect->h; ++j) {
                        bool should_draw = i == rect->x || i == rect->x + rect->w - 1
                                           || j == rect->y || j == rect->y + rect->h - 1;

                        if (should_draw)
                                gfx_draw_pixel(i, j, col);
                }
        }
}

void gfx_clear_screen(struct gfx_color col)
{
        uint64_t q = *(const uint64_t *)&col << 32 | *(const uint64_t *)&col;
        size_t writes = frame_buf.res_horiz * frame_buf.res_vert / 2;

        fast_memset(frame_buf.base, q, writes);
}

void gfx_draw_psf_glyph(int x, int y, wchar_t c, struct gfx_color col)
{
        const uint8_t *glyph = &psf_font.glyph_buf[c * psf_font.hdr.glyph_bytes];

        for (int j = 0; j < psf_font.hdr.height; ++j) {
                for (int i = 0; i < psf_font.hdr.width; ++i) {
                        int glyph_byte = j * psf_font.hdr.width / 8;
                        uint8_t bitmask = 1 << 7 >> i % 8;

                        if ((glyph[glyph_byte] & bitmask) > 0)
                                gfx_draw_pixel(x + i, y + j, col);
                }
        }
}

void gfx_draw_psf_string(int x, int y, const char *s, struct gfx_color col)
{
        for (int i = 0; s[i] != '\0'; ++i)
                gfx_draw_psf_glyph(x + i * 8, y, s[i], col);
}

void gfx_draw_psf_hex(int x, int y, const void *h, size_t size, struct gfx_color col)
{
        char char_map[16] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
        };

        gfx_draw_psf_string(x, y, "0x", col);

        for (size_t i = 0; i < size; ++i) {
                const uint8_t *b = (const uint8_t *)h + i;
                int x_off = psf_font.hdr.width * i * 2 + psf_font.hdr.width * 2;

                gfx_draw_psf_glyph(x + x_off, y, char_map[(*b & 0xf0) >> 4], col);
                gfx_draw_psf_glyph(x + x_off + psf_font.hdr.width, y, char_map[*b & 0xf], col);
        }
}

struct gfx_psf_font_header gfx_psf_font_info(void)
{
        return psf_font.hdr;
}
