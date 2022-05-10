#ifndef CPU_H_kPAI6RwO0zsVrHDXEjZHkr2DoYBiyqXQ
#define CPU_H_kPAI6RwO0zsVrHDXEjZHkr2DoYBiyqXQ

#include <stdint.h>

/* ===========
 * cpu_state.c
 * ===========
 */

union cpu_state_reg {
        uint64_t s64;
        uint32_t s32[2];
        uint16_t s16[4];
        uint8_t s8[8];
};

struct cpu_state_regs {
        union cpu_state_reg rax;
        union cpu_state_reg rbx;
        union cpu_state_reg rcx;
        union cpu_state_reg rdx;
        union cpu_state_reg rsi;
        union cpu_state_reg rdi;
        union cpu_state_reg rsp;
        union cpu_state_reg rbp;
};

struct cpu_state_regs cpu_state_regs(void);
void cpu_state_set_regs(const struct cpu_state_regs *regs);

/* =========
 * cpu_gdt.c
 * =========
 */

enum cpu_gdt_selector {
        CPU_GDT_SELECTOR_NULL = 0x0,
        CPU_GDT_SELECTOR_KERNEL_CODE = 0x8,
        CPU_GDT_SELECTOR_KERNEL_DATA = 0x10,
};

void cpu_gdt_init(void);

#endif
