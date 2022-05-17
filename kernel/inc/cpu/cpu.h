#ifndef _CPU_CPU_H_
#define _CPU_CPU_H_

#include <stdint.h>

union cpu_reg {
        uint64_t s64;
        uint32_t s32[2];
        uint16_t s16[4];
        uint8_t s8[8];
};

struct cpu_regs {
        union cpu_reg rax;
        union cpu_reg rbx;
        union cpu_reg rcx;
        union cpu_reg rdx;
        union cpu_reg rsi;
        union cpu_reg rdi;
        union cpu_reg rsp;
        union cpu_reg rbp;
};

struct cpu_regs cpu_regs(void);
void cpu_set_regs(const struct cpu_regs *regs);

#endif
