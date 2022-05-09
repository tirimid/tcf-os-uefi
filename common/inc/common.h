#ifndef COMMON_H_tsRcn7KhmuWfEuz4b7bhOfEnS0k5yLwZ
#define COMMON_H_tsRcn7KhmuWfEuz4b7bhOfEnS0k5yLwZ

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ========
 * graphics
 * ========
 */

struct com_gfx_frame_buf {
        void *base;
        size_t size;
        int res_horiz;
        int res_vert;
        int scanline_pixels;
};

struct com_gfx_psf_font_header {
        uint32_t magic;
        uint32_t ver;
        uint32_t hdr_size;
        uint32_t flags;
        uint32_t glyph_cnt;
        uint32_t glyph_bytes;
        uint32_t height;
        uint32_t width;
};

struct com_gfx_psf_font {
        struct com_gfx_psf_font_header hdr;
        uint8_t *glyph_buf;
};

/* ====
 * boot
 * ====
 */

struct com_boot_boot_info {
        struct com_gfx_frame_buf frame_buf;
        struct com_gfx_psf_font font;
        int page_size;
};

#endif
