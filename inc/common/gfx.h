#ifndef _COMMON_GFX_H_
#define _COMMON_GFX_H_

#include <stdint.h>
#include <stddef.h>

struct gfx_frame_buf {
        void *base;
        size_t size;
        int res_horiz;
        int res_vert;
        int scanline_pixels;
};

struct gfx_psf_font_header {
        uint32_t magic;
        uint32_t ver;
        uint32_t hdr_size;
        uint32_t flags;
        uint32_t glyph_cnt;
        uint32_t glyph_bytes;
        uint32_t height;
        uint32_t width;
};

struct gfx_psf_font {
        struct gfx_psf_font_header hdr;
        uint8_t *glyph_buf;
};

#endif
