#include "cpu/state.h"

struct cpu_state_regs cpu_state_regs(void)
{
        struct cpu_state_regs regs;

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

void cpu_state_set_regs(const struct cpu_state_regs *regs)
{
        __asm__("mov %0, %%rax\n"
                "mov %1, %%rbx\n"
                "mov %2, %%rcx\n"
                "mov %3, %%rdx\n"
                "mov %4, %%rsi\n"
                "mov %5, %%rdi\n"
                "mov %6, %%rsp\n"
                "mov %7, %%rbp\n"
                :
                : "m" (regs->rax), "m" (regs->rbx), "m" (regs->rcx), "m" (regs->rdx),
                  "m" (regs->rsi), "m" (regs->rdi), "m" (regs->rsp), "m" (regs->rbp));
}
