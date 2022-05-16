#ifndef KERNEL_INT_ISR_H
#define KERNEL_INT_ISR_H

#include <stdint.h>

struct int_isr_frame {
        uint64_t ip;
        uint64_t cs;
        uint64_t flags;
        uint64_t sp;
        uint64_t ss;
};

__attribute__((interrupt)) void int_isr_default(const struct int_isr_frame *frame);

__attribute__((interrupt)) void int_isr_div_by_0(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_debug(const struct int_isr_frame *frame);

__attribute__((interrupt)) void int_isr_double_fault(const struct int_isr_frame *frame,
                                                     uint64_t err_code);

__attribute__((interrupt)) void int_isr_gp_fault(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_page_fault(const struct int_isr_frame *frame);

__attribute__((interrupt)) void int_isr_pit(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_ps2_keyboard(const struct int_isr_frame *frame);

#endif
