#ifndef KERNEL_IO_GFX_H
#define KERNEL_IO_GFX_H

#include "comgfx.h"
#include <stdint.h>

void io_gfx_init(const struct com_gfx_frame_buf *_frame_buf,
                 const struct com_gfx_psf_font *_psf_font);

struct __attribute__((packed)) io_gfx_color {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t _ignore;
};

void io_gfx_draw_pixel(int x, int y, struct io_gfx_color col);

struct io_gfx_rect {
        int x;
        int y;
        int w;
        int h;
};

void io_gfx_draw_rect(const struct io_gfx_rect *rect, struct io_gfx_color col);
void io_gfx_draw_hollow_rect(const struct io_gfx_rect *rect, struct io_gfx_color col);
void io_gfx_clear_screen(struct io_gfx_color col);

void io_gfx_draw_psf_glyph(int x, int y, wchar_t c, struct io_gfx_color col);

#endif
