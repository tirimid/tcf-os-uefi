#include "kern.h"
#include "common.h"
#include "io.h"
#include <stddef.h>

__attribute__((ms_abi)) int main(const struct com_boot_info *info)
{
        kern_ctl_init(info);

        io_gfx_clear_screen((struct io_gfx_color){ 100, 0, 0 });

        for (int i = 0; i < 100; ++i)
                io_gfx_draw_psf_glyph(i * 8, 0, L'h', (struct io_gfx_color){ 255, 255, 255 });

        kern_ctl_hang();
        
        return 0;
}
