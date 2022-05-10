#ifndef IO_H_EyARGhaQwMzWaPsTTkfWP0va4eftzGvd
#define IO_H_EyARGhaQwMzWaPsTTkfWP0va4eftzGvd

#include "common.h"
#include <stdint.h>

/* ========
 * io_gfx.c
 * ========
 */

void io_gfx_init_gfx(const struct com_gfx_frame_buf *_frame_buf);

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

void io_gfx_init_psf(const struct com_gfx_psf_font *_psf_font);

void io_gfx_draw_psf_glyph(int x, int y, wchar_t c, struct io_gfx_color col);

/* ========
 * io_cpu.c
 * ========
 */

enum io_cpu_port {
        IO_CPU_PORT_PIC1_CTRL = 0x20,
        IO_CPU_PORT_PIC1_DATA = 0x21,
        IO_CPU_PORT_PIC2_CTRL = 0xa0,
        IO_CPU_PORT_PIC2_DATA = 0xa1,
};

void io_cpu_write_port_byte(enum io_cpu_port port, uint8_t b);
void io_cpu_write_port_word(enum io_cpu_port port, uint16_t w);
void io_cpu_write_port_long(enum io_cpu_port port, uint32_t l);

uint8_t io_cpu_read_port_byte(enum io_cpu_port port);
uint16_t io_cpu_read_port_word(enum io_cpu_port port);
uint32_t io_cpu_read_port_long(enum io_cpu_port port);

#endif
