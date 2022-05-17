#include "int/isr.h"

#include "sched/pit.h"
#include "int/pic.h"
#include "cpu/io.h"
#include "kern/error.h"

__attribute__((interrupt)) void isr_default(const struct isr_frame *frame)
{
}

__attribute__((interrupt)) void isr_div_by_0(const struct isr_frame *frame)
{
}

__attribute__((interrupt)) void isr_debug(const struct isr_frame *frame)
{
}

__attribute__((interrupt)) void isr_double_fault(const struct isr_frame *frame,
                                                 uint64_t err_code)
{
        error_panic(ERROR_PANIC_CODE_UNRECOVERABLE_DOUBLE_FAULT, "double fault");
}

__attribute__((interrupt)) void isr_gp_fault(const struct isr_frame *frame)
{
}

__attribute__((interrupt)) void isr_page_fault(const struct isr_frame *frame)
{
}

__attribute__((interrupt)) void isr_pit(const struct isr_frame *frame)
{
        sched_pit_tick();
        pic_end_pic1_int();
}

__attribute__((interrupt)) void isr_ps2_keyboard(const struct isr_frame *frame)
{
        uint8_t scancode = io_read_port_byte(IO_PORT_PS2_DATA);

        pic_end_pic1_int();
}
