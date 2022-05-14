#include "kern/ctl.h"
#include "comboot.h"
#include "io/gfx.h"
#include <stddef.h>
#include "mem/heap.h"
#include "mem/pgalloc.h"

__attribute__((ms_abi)) int main(const struct com_boot_info *info)
{
        kern_ctl_init(info);

        io_gfx_clear_screen((struct io_gfx_color){ 0, 0, 0 });
        io_gfx_draw_psf_string(0, 0, "hello world", (struct io_gfx_color){ 255, 255, 255 });

        for (int i = 0; i < 15; ++i) {
                void *ptr = mem_heap_alloc(10);
                
                io_gfx_draw_psf_hex(0, 16 + i * 16, &ptr, 8, (struct io_gfx_color){ 255, 255, 0 });
        }
        
        kern_ctl_hang();
        
        return 0;
}
