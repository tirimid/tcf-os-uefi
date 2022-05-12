#ifndef KERNEL_INT_PIC_H
#define KERNEL_INT_PIC_H

#include <stdint.h>

void int_pic_remap(uint8_t range_start_pic1, uint8_t range_start_pic2);
void int_pic_end_int(void);

#endif
