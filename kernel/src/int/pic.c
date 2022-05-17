#include "int/pic.h"

#include "cpu/io.h"

enum init_ctrl_word_1 {
        INIT_CTRL_WORD_1_INIT_CTRL_WORD_4 = 0x1,
        INIT_CTRL_WORD_1_INIT = 0x10,
};

enum init_ctrl_word_4 {
        INIT_CTRL_WORD_4_8086 = 0x1,
};

void pic_remap(uint8_t range_start_pic1, uint8_t range_start_pic2)
{
        uint8_t mask_1 = io_read_port_byte(IO_PORT_PIC1_DATA);
        uint8_t mask_2 = io_read_port_byte(IO_PORT_PIC2_DATA);

        io_write_port_byte(IO_PORT_PIC1_CTRL,
                           INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_INIT_CTRL_WORD_4);
        
        io_write_port_byte(IO_PORT_PIC2_CTRL,
                           INIT_CTRL_WORD_1_INIT | INIT_CTRL_WORD_1_INIT_CTRL_WORD_4);
        
        io_write_port_byte(IO_PORT_PIC1_DATA, range_start_pic1);
        io_write_port_byte(IO_PORT_PIC2_DATA, range_start_pic2);
        io_write_port_byte(IO_PORT_PIC1_DATA, 4);
        io_write_port_byte(IO_PORT_PIC2_DATA, 2);
        io_write_port_byte(IO_PORT_PIC1_DATA, INIT_CTRL_WORD_4_8086);
        io_write_port_byte(IO_PORT_PIC2_DATA, INIT_CTRL_WORD_4_8086);

        io_write_port_byte(IO_PORT_PIC1_DATA, mask_1);
        io_write_port_byte(IO_PORT_PIC2_DATA, mask_2);
}

void pic_mask(uint8_t pic1_mask, uint8_t pic2_mask)
{
        io_write_port_byte(IO_PORT_PIC1_DATA, pic1_mask);
        io_write_port_byte(IO_PORT_PIC2_DATA, pic2_mask);
}

__attribute__((no_caller_saved_registers)) void pic_end_pic1_int(void)
{
        io_write_port_byte(IO_PORT_PIC1_CTRL, 0x20);
}

void pic_end_pic2_int(void)
{
        io_write_port_byte(IO_PORT_PIC2_CTRL, 0x20);
        io_write_port_byte(IO_PORT_PIC1_CTRL, 0x20);
}
