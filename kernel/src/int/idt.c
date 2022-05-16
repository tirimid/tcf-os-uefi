#include "int/idt.h"

#include <stdint.h>
#include "cpu/gdt.h"
#include <stdbool.h>
#include "int/isr.h"

#define IDT_SIZE 256

struct __attribute__((packed)) idt_entry {
        uint16_t offset_0;
        uint16_t selector;
        uint8_t ist;
        uint8_t type_attr;
        uint16_t offset_1;
        uint32_t offset_2;
        uint32_t _zero;
};

static struct idt_entry idt[IDT_SIZE];

struct __attribute__((packed)) idt_reg {
        uint16_t size;
        uint64_t offset;
};

enum gate_type {
        GATE_TYPE_INTERRUPT = 0x8e,
        GATE_TYPE_TRAP = 0x8f,
};

static void set_idt_entry(int ind, const void *isr, enum gate_type gate_type)
{
        idt[ind] = (struct idt_entry){
                .offset_0 = (uintptr_t)isr & 0xffff,
                .offset_1 = ((uintptr_t)isr & 0xffff0000) >> 16,
                .offset_2 = ((uintptr_t)isr & 0xffffffff00000000) >> 32,
                .selector = CPU_GDT_SELECTOR_KERNEL_CODE,
                .type_attr = gate_type,
                .ist = 0,
                ._zero = 0,
        };
}

void int_idt_init(void)
{
        static bool initialized = false;

        if (initialized)
                return;

        for (int i = 0; i < IDT_SIZE; ++i)
                set_idt_entry(i, (const void *)int_isr_default, GATE_TYPE_INTERRUPT);

        set_idt_entry(0x0, (const void *)int_isr_div_by_0, GATE_TYPE_INTERRUPT);
        set_idt_entry(0x1, (const void *)int_isr_debug, GATE_TYPE_TRAP);
        set_idt_entry(0x8, (const void *)int_isr_double_fault, GATE_TYPE_INTERRUPT);
        set_idt_entry(0xd, (const void *)int_isr_gp_fault, GATE_TYPE_INTERRUPT);
        set_idt_entry(0xe, (const void *)int_isr_page_fault, GATE_TYPE_INTERRUPT);

        set_idt_entry(0x20, (const void *)int_isr_pit, GATE_TYPE_INTERRUPT);
        set_idt_entry(0x21, (const void *)int_isr_ps2_keyboard, GATE_TYPE_INTERRUPT);
        
        struct idt_reg idtr = {
                .offset = (uintptr_t)idt,
                .size = sizeof(idt),
        };

        __asm__("lidt %0\n"
                :
                : "m" (idtr));

        initialized = true;
}
