#ifndef COMMON_COMBOOT_H
#define COMMON_COMBOOT_H

#include "comgfx.h"
#include "commem.h"

struct com_boot_info {
        struct com_gfx_frame_buf frame_buf;
        struct com_gfx_psf_font font;
        struct com_mem_map mem_map;
        int page_size;
};

#endif
