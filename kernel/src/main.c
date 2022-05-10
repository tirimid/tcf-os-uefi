#include "kern.h"
#include "common.h"
#include "io.h"
#include <stddef.h>

__attribute__((ms_abi)) int main(const struct com_boot_info *info)
{
        kern_ctl_init(info);

        io_gfx_clear_screen((struct io_gfx_color){ 100, 0, 0 });
        io_gfx_draw_psf_glyph(0, 0, L'h', (struct io_gfx_color){ 255, 255, 255 });
        io_gfx_draw_psf_glyph(8, 0, L'i', (struct io_gfx_color){ 255, 255, 255 });

        kern_ctl_hang();
        
        return 0;
}
