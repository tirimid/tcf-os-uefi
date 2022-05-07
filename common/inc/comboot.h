#ifndef BOOTTYPES_H_tsRcn7KhmuWfEuz4b7bhOfEnS0k5yLwZ
#define BOOTTYPES_H_tsRcn7KhmuWfEuz4b7bhOfEnS0k5yLwZ

#include "comgfx.h"

struct boot_info {
        struct frame_buf frame_buf;
        struct psf_font font;
        int page_size;
};

#endif
