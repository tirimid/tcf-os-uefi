#ifndef _INT_ISR_H_
#define _INT_ISR_H_

#include <stdint.h>

struct isr_frame {
        uint64_t ip;
        uint64_t cs;
        uint64_t flags;
        uint64_t sp;
        uint64_t ss;
};

__attribute__((interrupt)) void isr_default(const struct isr_frame *frame);

__attribute__((interrupt)) void isr_div_by_0(const struct isr_frame *frame);
__attribute__((interrupt)) void isr_debug(const struct isr_frame *frame);

__attribute__((interrupt)) void isr_double_fault(const struct isr_frame *frame,
                                                 uint64_t err_code);

__attribute__((interrupt)) void isr_gp_fault(const struct isr_frame *frame);
__attribute__((interrupt)) void isr_page_fault(const struct isr_frame *frame);

__attribute__((interrupt)) void isr_pit(const struct isr_frame *frame);
__attribute__((interrupt)) void isr_ps2_keyboard(const struct isr_frame *frame);

#endif
