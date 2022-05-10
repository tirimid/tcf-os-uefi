#include "int.h"

#include "io.h"

__attribute__((interrupt)) void int_isr_default_isr(const struct int_isr_int_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_div_by_0_isr(const struct int_isr_int_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_debug_isr(const struct int_isr_int_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_gp_fault_isr(const struct int_isr_int_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_page_fault_isr(const struct int_isr_int_frame *frame)
{
}
