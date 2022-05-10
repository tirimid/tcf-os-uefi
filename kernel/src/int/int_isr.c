#include "int.h"

#include "io.h"

__attribute__((interrupt)) void int_isr_default(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_div_by_0(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_debug(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_gp_fault(const struct int_isr_frame *frame)
{
}

__attribute__((interrupt)) void int_isr_page_fault(const struct int_isr_frame *frame)
{
}
