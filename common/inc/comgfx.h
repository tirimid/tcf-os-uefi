#ifndef GFXTYPES_H_EzXfdykIneJUL7C2Yf2Y4YxDGylaFdKj
#define GFXTYPES_H_EzXfdykIneJUL7C2Yf2Y4YxDGylaFdKj

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct frame_buf {
        void *base;
        size_t size;
        int res_horiz;
        int res_vert;
        int scanline_pixels;
};

struct psf_font_header {
        uint32_t magic;
        uint32_t ver;
        uint32_t hdr_size;
        uint32_t flags;
        uint32_t glyph_cnt;
        uint32_t glyph_bytes;
        uint32_t height;
        uint32_t width;
};

struct psf_font {
        struct psf_font_header hdr;
        uint8_t *glyph_buf;
};

#endif
