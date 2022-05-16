        .ifndef KERNEL_CPU_GDT_S
        .equ KERNEL_CPU_GDT_S, 1

        .globl cpu_gdt_load
cpu_gdt_load:
                lgdt (%rdi)

                mov $0x10, %ax
                mov %ax, %ds
                mov %ax, %es
                mov %ax, %fs
                mov %ax, %gs
                mov %ax, %ss

                pop %rdi
                mov $0x8, %rax
                push %rax
                push %rdi

                retfq

        .endif
