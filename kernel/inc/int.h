#ifndef INT_H_U3fP5S0jqOGfy9gXabJ5BTg0Qh4ImzEg
#define INT_H_U3fP5S0jqOGfy9gXabJ5BTg0Qh4ImzEg

#include <stdint.h>

/* =========
 * int_idt.c
 * =========
 */

void int_idt_init(void);

/* =========
 * int_isr.c
 * =========
 */

struct int_isr_frame;

__attribute__((interrupt)) void int_isr_default(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_div_by_0(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_debug(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_gp_fault(const struct int_isr_frame *frame);
__attribute__((interrupt)) void int_isr_page_fault(const struct int_isr_frame *frame);

/* =========
 * int_pic.c
 * =========
 */

void int_pic_remap(uint8_t range_start_pic1, uint8_t range_start_pic2);
void int_pic_end_int(void);

#endif
