#include "int/pic.h"

#include "io/cpu.h"

enum init_ctrl_word_1 {
        INIT_CTRL_WORD_1_INIT_CTRL_WORD_4 = 0x1,
        INIT_CTRL_WORD_1_INIT = 0x10,
};

enum init_ctrl_word_4 {
        INIT_CTRL_WORD_4_8086 = 0x1,
};

void int_pic_remap(uint8_t range_start_pic1, uint8_t range_start_pic2)
{
        /* remap pic1 */
        uint8_t mask = io_cpu_read_port_byte(IO_CPU_PORT_PIC1_DATA);

        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_CTRL,
                               INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_INIT_CTRL_WORD_4);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, range_start_pic1);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, 4);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, INIT_CTRL_WORD_4_8086);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_DATA, mask);
        
        /* remap pic2 */
        mask = io_cpu_read_port_byte(IO_CPU_PORT_PIC2_DATA);

        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_CTRL,
                               INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_INIT_CTRL_WORD_4);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, range_start_pic2);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, 2);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, INIT_CTRL_WORD_4_8086);
        
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_DATA, mask);
}

void int_pic_end_int(void)
{
        io_cpu_write_port_byte(IO_CPU_PORT_PIC2_CTRL, 0x20);
        io_cpu_write_port_byte(IO_CPU_PORT_PIC1_CTRL, 0x20);
}
