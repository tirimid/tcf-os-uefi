#include "int.h"

#include "io.h"

enum init_ctrl_word_1 {
        INIT_CTRL_WORD_1_INIT_CTRL_WORD_4 = 0x1,
        INIT_CTRL_WORD_1_INIT = 0x10,
};

enum init_ctrl_word_4 {
        INIT_CTRL_WORD_4_8086 = 0x1,
};

void int_pic_remap_pic_1(uint8_t range_start)
{
        uint8_t mask = io_cpu_read_port_byte(IO_CPU_PORT_PIC1_DATA);

        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_CTRL,
                               INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_INIT_CTRL_WORD_4);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, range_start);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, 4);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, INIT_CTRL_WORD_4_8086);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, mask);
}

void int_pic_remap_pic_2(uint8_t range_start)
{
        uint8_t mask = io_cpu_read_port_byte(IO_CPU_PORT_PIC2_DATA);

        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_CTRL,
                               INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_INIT_CTRL_WORD_4);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, range_start);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, 2);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, INIT_CTRL_WORD_4_8086);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, mask);
}

void int_pic_end_pic_1_int(void)
{
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_CTRL, 0x20);
}

void int_pic_end_pic_2_int(void)
{
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_CTRL, 0x20);
}

void int_pic_end_int(void)
{
        int_pic_end_pic_2_int();
        int_pic_end_pic_1_int();
}
