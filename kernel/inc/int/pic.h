#ifndef INT_PIC_H__
#define INT_PIC_H__

#include <stdint.h>

void pic_remap(uint8_t range_start_pic1, uint8_t range_start_pic2);
void pic_mask(uint8_t pic1_mask, uint8_t pic2_mask);

__attribute__((no_caller_saved_registers)) void pic_end_pic1_int(void);
void pic_end_pic2_int(void);

#endif
