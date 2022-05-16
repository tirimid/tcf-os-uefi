#ifndef KERNEL_SCHED_PIT_H
#define KERNEL_SCHED_PIT_H

#include <stdint.h>

void sched_pit_init(uint16_t _div);

void sched_pit_sleep(uint64_t millis);
__attribute__((no_caller_saved_registers)) void sched_pit_tick(void);

double sched_pit_approx_uptime(void);

#endif
