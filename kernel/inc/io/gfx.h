#ifndef _IO_GFX_H_
#define _IO_GFX_H_

#include "common/gfx.h"
#include <stdint.h>
#include <stddef.h>

#define GFX_COLOR_BLACK ((struct gfx_color){ 0, 0, 0 })
#define GFX_COLOR_RED ((struct gfx_color){ 0, 0, 255 })
#define GFX_COLOR_GREEN ((struct gfx_color){ 0, 255, 0 })
#define GFX_COLOR_YELLOW ((struct gfx_color){ 0, 255, 255 })
#define GFX_COLOR_BLUE ((struct gfx_color){ 255, 0, 0 })
#define GFX_COLOR_PURPLE ((struct gfx_color){ 255, 0, 255 })
#define GFX_COLOR_CYAN ((struct gfx_color){ 255, 255, 0 })
#define GFX_COLOR_WHITE ((struct gfx_color){ 255, 255, 255 })

void gfx_init(const struct gfx_frame_buf *_frame_buf, const struct gfx_psf_font *_psf_font);

struct __attribute__((packed)) gfx_color {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t _ignore;
};

void gfx_draw_pixel(int x, int y, struct gfx_color col);

struct gfx_rect {
        int x;
        int y;
        int w;
        int h;
};

void gfx_draw_rect(const struct gfx_rect *rect, struct gfx_color col);
void gfx_draw_hollow_rect(const struct gfx_rect *rect, struct gfx_color col);
void gfx_clear_screen(struct gfx_color col);

void gfx_draw_psf_glyph(int x, int y, wchar_t c, struct gfx_color col);
void gfx_draw_psf_string(int x, int y, const char *s, struct gfx_color col);
void gfx_draw_psf_hex(int x, int y, const void *h, size_t size, struct gfx_color col);

struct gfx_psf_font_header gfx_psf_font_info(void);

#endif
