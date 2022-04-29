#include "kernel.h"
#include "boottypes.h"
#include "io/gfx.h"

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
        hang();
        return 0;
}
