#include "kern/ctl.h"
#include "comboot.h"
#include "io/gfx.h"
#include <stddef.h>
#include "mem/pgalloc.h"

__attribute__((ms_abi)) int main(struct com_boot_info *info)
{
        kern_ctl_init(info);

        io_gfx_clear_screen((struct io_gfx_color){ 100, 0, 0 });
        io_gfx_draw_psf_string(0, 0, "hello world", (struct io_gfx_color){ 255, 255, 255 });

        void *page = mem_pgalloc_request_pages(3);
        io_gfx_draw_psf_hex(0, 16, page, sizeof(page), (struct io_gfx_color){ 255, 255, 255 });
        page = mem_pgalloc_request_pages(3);
        io_gfx_draw_psf_hex(0, 32, page, sizeof(page), (struct io_gfx_color){ 255, 255, 255 });
        page = mem_pgalloc_request_pages(3);
        io_gfx_draw_psf_hex(0, 48, page, sizeof(page), (struct io_gfx_color){ 255, 255, 255 });

        kern_ctl_hang();
        
        return 0;
}
