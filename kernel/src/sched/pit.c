#include "sched/pit.h"

#include "cpu/io.h"
#include <stdbool.h>

static double approx_uptime = 0.0;
static uint16_t div;

void pit_init(uint16_t _div)
{
        static bool initialized = false;

        if (initialized)
                return;

        div = _div > 50 ? _div : 50;

        io_write_port_byte(IO_PORT_PIT_DATA_0, div & 0xff);
        io_write_port_byte(IO_PORT_PIT_DATA_0, (div & 0xff00) >> 8);

        initialized = true;
}

void pit_sleep(uint64_t millis)
{
        double start_time = approx_uptime;

        while (approx_uptime < start_time + (double)millis / 1000.0)
                __asm__("hlt\n");
}

__attribute__((no_caller_saved_registers)) void pit_tick(void)
{
        approx_uptime += 1.0 / (double)(1193182 / div);
}

double pit_approx_uptime(void)
{
        return approx_uptime;
}
