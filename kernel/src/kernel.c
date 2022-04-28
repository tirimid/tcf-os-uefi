#include "kernel.h"

#include <stdbool.h>

void
init_kernel(void)
{
}

void
hang(void)
{
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
