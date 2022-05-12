#include "kern/ctl.h"
#include "comboot.h"
#include "io/gfx.h"
#include <stddef.h>

__attribute__((ms_abi)) int main(struct com_boot_info *info)
{
        kern_ctl_init(info);

        io_gfx_clear_screen((struct io_gfx_color){ 100, 0, 0 });
        io_gfx_draw_psf_string(0, 0, "hello world", (struct io_gfx_color){ 255, 255, 255 });
        
        kern_ctl_hang();
        
        return 0;
}
