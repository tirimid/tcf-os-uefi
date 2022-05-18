#ifndef CPU_GDT_H__
#define CPU_GDT_H__

enum gdt_selector {
        GDT_SELECTOR_KERNEL_NULL = 0x0,
        GDT_SELECTOR_KERNEL_CODE = 0x8,
        GDT_SELECTOR_KERNEL_DATA = 0x10,
};

void gdt_init(void);

#endif
