#ifndef KERNEL_IO_CPU_H
#define KERNEL_IO_CPU_H

#include <stdint.h>

enum io_cpu_port {
        IO_CPU_PORT_PIC1_CTRL = 0x20,
        IO_CPU_PORT_PIC1_DATA = 0x21,
        IO_CPU_PORT_PIT_DATA_0 = 0x40,
        IO_CPU_PORT_PIT_DATA_1 = 0x41,
        IO_CPU_PORT_PIT_DATA_2 = 0x42,
        IO_CPU_PORT_PIT_CTRL = 0x43,
        IO_CPU_PORT_PS2_DATA = 0x60,
        IO_CPU_PORT_PS2_STATUS_CTRL = 0x64,
        IO_CPU_PORT_PIC2_CTRL = 0xa0,
        IO_CPU_PORT_PIC2_DATA = 0xa1,
};

void io_cpu_write_port_byte(enum io_cpu_port port, uint8_t b);
void io_cpu_write_port_word(enum io_cpu_port port, uint16_t w);
void io_cpu_write_port_long(enum io_cpu_port port, uint32_t l);

__attribute__((no_caller_saved_registers)) uint8_t io_cpu_read_port_byte(enum io_cpu_port port);
uint16_t io_cpu_read_port_word(enum io_cpu_port port);
uint32_t io_cpu_read_port_long(enum io_cpu_port port);

#endif
