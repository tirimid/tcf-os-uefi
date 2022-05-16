#ifndef KERNEL_IO_GFX_H
#define KERNEL_IO_GFX_H

#include "comgfx.h"
#include <stdint.h>
#include <stddef.h>

#define IO_GFX_COLOR_BLACK ((struct io_gfx_color){ 0, 0, 0 })
#define IO_GFX_COLOR_RED ((struct io_gfx_color){ 0, 0, 255 })
#define IO_GFX_COLOR_GREEN ((struct io_gfx_color){ 0, 255, 0 })
#define IO_GFX_COLOR_YELLOW ((struct io_gfx_color){ 0, 255, 255 })
#define IO_GFX_COLOR_BLUE ((struct io_gfx_color){ 255, 0, 0 })
#define IO_GFX_COLOR_PURPLE ((struct io_gfx_color){ 255, 0, 255 })
#define IO_GFX_COLOR_CYAN ((struct io_gfx_color){ 255, 255, 0 })
#define IO_GFX_COLOR_WHITE ((struct io_gfx_color){ 255, 255, 255 })

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
void io_gfx_draw_psf_string(int x, int y, const char *s, struct io_gfx_color col);
void io_gfx_draw_psf_hex(int x, int y, const void *h, size_t size, struct io_gfx_color col);

struct com_gfx_psf_font_header io_gfx_psf_font_info(void);

#endif
