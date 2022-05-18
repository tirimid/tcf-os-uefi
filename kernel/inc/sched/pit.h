#ifndef SCHED_PIT_H__
#define SCHED_PIT_H__

#include <stdint.h>

void pit_init(uint16_t _div);

void pit_sleep(uint64_t millis);
__attribute__((no_caller_saved_registers)) void pit_tick(void);

double pit_approx_uptime(void);

#endif
