#ifndef BOOTTYPES_H_tsRcn7KhmuWfEuz4b7bhOfEnS0k5yLwZ
#define BOOTTYPES_H_tsRcn7KhmuWfEuz4b7bhOfEnS0k5yLwZ

#include <stddef.h>

struct frame_buf {
        void *base;
        size_t size;
        int res_horiz;
        int res_vert;
        int scanline_pixels;
};

struct boot_info {
        struct frame_buf frame_buf;
};

#endif
