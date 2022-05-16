#ifndef KERNEL_INT_PIC_H
#define KERNEL_INT_PIC_H

#include <stdint.h>

void int_pic_remap(uint8_t range_start_pic1, uint8_t range_start_pic2);
void int_pic_mask(uint8_t pic1_mask, uint8_t pic2_mask);

__attribute__((no_caller_saved_registers)) void int_pic_end_pic1_int(void);
void int_pic_end_pic2_int(void);

#endif
