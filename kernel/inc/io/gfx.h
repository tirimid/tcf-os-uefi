#ifndef GFX_H_GepUhQPiKyApki1gEaDUB4jLOVt2OUdu
#define GFX_H_GepUhQPiKyApki1gEaDUB4jLOVt2OUdu

#include "boottypes.h"
#include <stdint.h>

void
init_gfx(const struct frame_buf *fb_in_use);

/* color is written to memory in little endian way, so members are in a
 * reversed order here
 */
struct __attribute__((packed)) color {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t _ignore;
};

void
draw_pixel(int x, int y, struct color col);

void
draw_box(int x, int y, int w, int h, struct color col);

void
clear_screen(struct color col);

#endif