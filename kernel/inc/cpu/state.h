#ifndef KERNEL_CPU_STATE_H
#define KERNEL_CPU_STATE_H

#include <stdint.h>

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

#endif
