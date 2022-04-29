#ifndef PSF_H_6PML0yZCMIJt3yN49rqkx3jJlYuLfNjl
#define PSF_H_6PML0yZCMIJt3yN49rqkx3jJlYuLfNjl

#include "gfxtypes.h"
#include "gfx.h"

void
init_psf(const struct psf_font *font_in_use);

void
draw_psf_glyph(int x, int y, int c, struct color col);

#endif
