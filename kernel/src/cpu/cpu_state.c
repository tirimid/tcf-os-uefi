#include "cpu.h"

struct cpu_state_cpu_regs cpu_state_cpu_regs(void)
{
        struct cpu_state_cpu_regs regs;

        __asm__("mov %%rax, %0\n"
                "mov %%rbx, %1\n"
                "mov %%rcx, %2\n"
                "mov %%rdx, %3\n"
                "mov %%rsi, %4\n"
                "mov %%rdi, %5\n"
                "mov %%rsp, %6\n"
                "mov %%rbp, %7\n"
                : "=m" (regs.rax), "=m" (regs.rbx), "=m" (regs.rcx), "=m" (regs.rdx),
                  "=m" (regs.rsi), "=m" (regs.rdi), "=m" (regs.rsp), "=m" (regs.rbp));

        return regs;
}
