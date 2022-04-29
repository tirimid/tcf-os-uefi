#include "kernel.h"
#include "boottypes.h"
#include "io/gfx.h"
#include "io/psf.h"

__attribute__((ms_abi)) int
kernel_main(const struct boot_info *info)
{
        init_kernel(info);
        struct color c = {
                .r = 0,
                .g = 0,
                .b = 0,
        };
        clear_screen(c);
        c = (struct color){
                .r = 0,
                .g = 255,
                .b = 0,
        };
        draw_psf_glyph(0, 0, 'h', c);
        draw_psf_glyph(8, 0, 'e', c);
        draw_psf_glyph(16, 0, 'l', c);
        draw_psf_glyph(24, 0, 'l', c);
        draw_psf_glyph(32, 0, 'o', c);
        hang();
        return 0;
}
