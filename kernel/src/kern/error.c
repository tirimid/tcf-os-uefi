#include "kern/error.h"

#include "io/gfx.h"
#include <stdbool.h>

static const char *panic_code_str[] = {
        "VITAL_INIT_FAIL",
        "MEMORY_FAIL",
        "UNRECOVERABLE_DOUBLE_FAULT",
};

__attribute__((no_caller_saved_registers)) void kern_error_panic(enum kern_error_panic_code code,
                                                                 const char *msg)
{
        io_gfx_clear_screen(IO_GFX_COLOR_RED);
        io_gfx_draw_psf_string(0, 0, "kernel panic", IO_GFX_COLOR_WHITE);
        
        io_gfx_draw_psf_string(0, io_gfx_psf_font_info().height, panic_code_str[code],
                               IO_GFX_COLOR_WHITE);
        
        io_gfx_draw_psf_string(0, io_gfx_psf_font_info().height * 2, msg, IO_GFX_COLOR_WHITE);

        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
