#ifndef KERNEL_CPU_GDT_H
#define KERNEL_CPU_GDT_H

enum cpu_gdt_selector {
        CPU_GDT_SELECTOR_KERNEL_NULL = 0x0,
        CPU_GDT_SELECTOR_KERNEL_CODE = 0x8,
        CPU_GDT_SELECTOR_KERNEL_DATA = 0x10,
};

void cpu_gdt_init(void);

#endif
