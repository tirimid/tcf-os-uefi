#ifndef INT_H_U3fP5S0jqOGfy9gXabJ5BTg0Qh4ImzEg
#define INT_H_U3fP5S0jqOGfy9gXabJ5BTg0Qh4ImzEg

#include <stdint.h>

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
__attribute__((interrupt)) void int_isr_div_by_0_isr(const struct int_isr_int_frame *frame);
__attribute__((interrupt)) void int_isr_debug_isr(const struct int_isr_int_frame *frame);
__attribute__((interrupt)) void int_isr_gp_fault_isr(const struct int_isr_int_frame *frame);
__attribute__((interrupt)) void int_isr_page_fault_isr(const struct int_isr_int_frame *frame);

/* =========
 * int_pic.c
 * =========
 */

void int_pic_remap_pic_1(uint8_t range_start);
void int_pic_remap_pic_2(uint8_t range_start);

void int_pic_end_pic_1_int(void);
void int_pic_end_pic_2_int(void);
void int_pic_end_int(void);

#endif
