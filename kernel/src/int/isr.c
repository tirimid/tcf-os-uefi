#include "int/isr.h"

#include "sched/pit.h"
#include "int/pic.h"
#include "io/cpu.h"
#include "kern/error.h"

__attribute__((interrupt)) void int_isr_default(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_div_by_0(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_debug(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_double_fault(const struct int_isr_frame *frame,
                                                     uint64_t err_code)
{
        kern_error_panic(KERN_ERROR_PANIC_CODE_UNRECOVERABLE_DOUBLE_FAULT, "double fault");
}

__attribute__((interrupt)) void int_isr_gp_fault(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_page_fault(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_pit(const struct int_isr_frame *frame)
{
        sched_pit_tick();
        int_pic_end_pic1_int();
}

__attribute__((interrupt)) void int_isr_ps2_keyboard(const struct int_isr_frame *frame)
{
        uint8_t scancode = io_cpu_read_port_byte(IO_CPU_PORT_PS2_DATA);

        int_pic_end_pic1_int();
}
