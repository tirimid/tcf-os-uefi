        .ifndef CPU_GDT_S__
        .equ CPU_GDT_S__, 1

        .globl gdt_load
gdt_load:
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
