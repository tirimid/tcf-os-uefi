#include "int.h"

#include <stdint.h>
#include "cpu.h"

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

static void set_idt_entry(int ind, void (*isr)(const struct int_isr_int_frame *frame),
                          enum gate_type gate_type)
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

void int_idt_init_idt(void)
{
        for (int i = 0; i < IDT_SIZE; ++i)
                set_idt_entry(i, int_isr_default_isr, GATE_TYPE_INTERRUPT);

        set_idt_entry(0x0, int_isr_div_by_0_isr, GATE_TYPE_INTERRUPT);
        set_idt_entry(0x1, int_isr_debug_isr, GATE_TYPE_TRAP);
        set_idt_entry(0xd, int_isr_gp_fault_isr, GATE_TYPE_INTERRUPT);
        set_idt_entry(0xe, int_isr_page_fault_isr, GATE_TYPE_INTERRUPT);
        
        struct idt_reg idtr = {
                .offset = (uintptr_t)idt,
                .size = sizeof(idt),
        };

        __asm__("lidt %0\n"
                :
                : "m" (idtr));
}
