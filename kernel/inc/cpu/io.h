#ifndef _CPU_IO_H_
#define _CPU_IO_H_

#include <stdint.h>

enum io_port {
        IO_PORT_PIC1_CTRL = 0x20,
        IO_PORT_PIC1_DATA = 0x21,
        IO_PORT_PIT_DATA_0 = 0x40,
        IO_PORT_PIT_DATA_1 = 0x41,
        IO_PORT_PIT_DATA_2 = 0x42,
        IO_PORT_PIT_CTRL = 0x43,
        IO_PORT_PS2_DATA = 0x60,
        IO_PORT_PS2_STATUS_CTRL = 0x64,
        IO_PORT_PIC2_CTRL = 0xa0,
        IO_PORT_PIC2_DATA = 0xa1,
};

void io_write_port_byte(enum io_port port, uint8_t b);
void io_write_port_word(enum io_port port, uint16_t w);
void io_write_port_long(enum io_port port, uint32_t l);

__attribute__((no_caller_saved_registers)) uint8_t io_read_port_byte(enum io_port port);
uint16_t io_read_port_word(enum io_port port);
uint32_t io_read_port_long(enum io_port port);

#endif
