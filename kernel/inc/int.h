#ifndef INT_H_U3fP5S0jqOGfy9gXabJ5BTg0Qh4ImzEg
#define INT_H_U3fP5S0jqOGfy9gXabJ5BTg0Qh4ImzEg

/* =========
 * int_idt.c
 * =========
 */

void int_idt_init_idt(void);

/* =========
 * int_isr.c
 * =========
 */

struct int_isr_int_frame;

__attribute__((interrupt)) void int_isr_default_isr(const struct int_isr_int_frame *frame);
__attribute__((interrupt)) void int_isr_debug_isr(const struct int_isr_int_frame *frame);
__attribute__((interrupt)) void int_isr_page_fault_isr(const struct int_isr_int_frame *frame);
__attribute__((interrupt)) void int_isr_gp_fault_isr(const struct int_isr_int_frame *frame);

#endif
