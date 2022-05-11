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

/* ======
 * memory
 * ======
 */

struct com_mem_map_entry {
        uint32_t type;
        void *phys_start;
        void *virt_start;
        uint64_t page_cnt;
        uint64_t attr;
};

struct com_mem_map {
        struct com_mem_map_entry *map;
        size_t ent_size;
        int entries;
};

/* ====
 * boot
 * ====
 */

struct com_boot_info {
        struct com_gfx_frame_buf frame_buf;
        struct com_gfx_psf_font font;
        struct com_mem_map mem_map;
        int page_size;
};

#endif
