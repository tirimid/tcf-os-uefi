#include "io/psf.h"

#include <stdbool.h>
#include <stdint.h>

static struct psf_font font;

void
init_psf(const struct psf_font *font_in_use)
{
        font = *font_in_use;
}

void
draw_psf_glyph(int x, int y, int c, struct color col)
{
        const uint8_t *glyph = &font.glyph_buf[c * font.hdr.glyph_bytes];
        for (int j = 0; j < font.hdr.height; ++j) {
                for (int i = 0; i < font.hdr.width; ++i) {
                        uint8_t mask = 1 << 7 >> i;
                        if ((glyph[j] & mask) > 0)
                                draw_pixel(x + i, y + j, col);
                }
        }
}
