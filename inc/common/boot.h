#ifndef COMMON_BOOT_H__
#define COMMON_BOOT_H__

#include "gfx.h"
#include "mem.h"

struct boot_info {
        struct gfx_frame_buf frame_buf;
        struct gfx_psf_font font;
        struct mem_map mem_map;
        size_t page_size;
};

#endif
