#ifndef _CPU_GDT_H_
#define _CPU_GDT_H_

enum gdt_selector {
        GDT_SELECTOR_KERNEL_NULL = 0x0,
        GDT_SELECTOR_KERNEL_CODE = 0x8,
        GDT_SELECTOR_KERNEL_DATA = 0x10,
};

void gdt_init(void);

#endif
