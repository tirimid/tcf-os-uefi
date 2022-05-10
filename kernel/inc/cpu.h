#ifndef CPU_H_kPAI6RwO0zsVrHDXEjZHkr2DoYBiyqXQ
#define CPU_H_kPAI6RwO0zsVrHDXEjZHkr2DoYBiyqXQ

#include <stdint.h>

/* ===========
 * cpu_state.c
 * ===========
 */

union cpu_state_register {
        uint64_t s64;
        uint32_t s32[2];
        uint16_t s16[4];
        uint8_t s8[8];
};

struct cpu_state_cpu_regs {
        union cpu_state_register rax;
        union cpu_state_register rbx;
        union cpu_state_register rcx;
        union cpu_state_register rdx;
        union cpu_state_register rsi;
        union cpu_state_register rdi;
        union cpu_state_register rsp;
        union cpu_state_register rbp;
};

struct cpu_state_cpu_regs cpu_state_cpu_regs(void);

/* =========
 * cpu_gdt.c
 * =========
 */

enum cpu_gdt_selector {
        CPU_GDT_SELECTOR_NULL = 0x0,
        CPU_GDT_SELECTOR_KERNEL_CODE = 0x8,
        CPU_GDT_SELECTOR_KERNEL_DATA = 0x10,
};

void cpu_gdt_init_gdt(void);

#endif
