#include "io/gfx/psf.h"

static struct psf_font psf_font;

void init_psf(const struct psf_font *font_in_use)
{
        psf_font = *font_in_use;
}

void draw_psf_glyph(int x, int y, wchar_t c, struct color col)
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
