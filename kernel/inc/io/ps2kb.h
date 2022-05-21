#ifndef IO_PS2KB_H__
#define IO_PS2KB_H__

#include <stdint.h>

enum ps2kb_layout {
        PS2KB_LAYOUT_QWERTY,
        PS2KB_LAYOUT_COLEMAK,
};

void ps2kb_init(enum ps2kb_layout layout);

__attribute__((no_caller_saved_registers)) void ps2kb_handle_input(uint8_t scancode);

#endif
