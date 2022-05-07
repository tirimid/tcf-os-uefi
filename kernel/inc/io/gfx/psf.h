#ifndef PSF_H_z4WQuZNBDby3ikqWN8HKRSCG6GUpQZfp
#define PSF_H_z4WQuZNBDby3ikqWN8HKRSCG6GUpQZfp

#include "comgfx.h"
#include "io/gfx/gfx.h"

void
init_psf(const struct psf_font *font_in_use);

void
draw_psf_glyph(int x, int y, wchar_t c, struct color col);

#endif
