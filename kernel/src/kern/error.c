#include "kern/error.h"

#include "io/gfx.h"
#include <stdbool.h>

static const char *panic_code_str[] = {
        "VITAL_INIT_FAIL",
        "MEMORY_FAIL",
        "UNRECOVERABLE_DOUBLE_FAULT",
};

__attribute__((no_caller_saved_registers)) void error_panic(enum error_panic_code code,
                                                            const char *msg)
{
        gfx_clear_screen(GFX_COLOR_RED);
        gfx_draw_psf_string(0, 0, "kernel panic", GFX_COLOR_WHITE);
        
        gfx_draw_psf_string(0, gfx_psf_font_info().height, panic_code_str[code], GFX_COLOR_WHITE);
        gfx_draw_psf_string(0, gfx_psf_font_info().height * 2, msg, GFX_COLOR_WHITE);

        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
