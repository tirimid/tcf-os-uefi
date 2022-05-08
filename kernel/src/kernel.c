#include "kernel.h"

#include "io/gfx/gfx.h"
#include <stdbool.h>
#include "io/gfx/psf.h"
#include "mem/pgalloc.h"

void init_kernel(const struct boot_info *info)
{
        init_gfx(&info->frame_buf);
        init_psf(&info->font);
        init_page_alloc(info->page_size);
}

void hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
