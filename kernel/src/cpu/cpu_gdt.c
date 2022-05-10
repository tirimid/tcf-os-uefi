#include "cpu.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>

struct __attribute__((packed)) gdt_entry {
        uint16_t limit_0;
        uint16_t base_0;
        uint8_t base_1;
        bool accessed : 1;
        bool read_write : 1;
        bool dir_conform : 1;
        bool exec : 1;
        bool desc_type : 1;
        uint8_t privelege : 2;
        bool present : 1;
        uint8_t limit_1 : 4;
        bool _reserved : 1;
        bool long_mode_code : 1;
        bool protected_mode : 1;
        bool granularity : 1;
        uint8_t base_2;
};

alignas(0x1000) static struct gdt_entry gdt[3] = {
        /* null segment */
        (struct gdt_entry){ 0 },
        
        /* kernel code segment */
        (struct gdt_entry){
                .base_0 = 0x0,
                .base_1 = 0x0,
                .base_2 = 0x0,
                .limit_0 = 0xffff,
                .limit_1 = 0xf,
                .accessed = false,
                .read_write = false,
                .dir_conform = false,
                .exec = true,
                .desc_type = true,
                .privelege = 0,
                .present = true,
                .long_mode_code = true,
                .protected_mode = false,
                .granularity = true,
        },
        
        /* kernel data segment */
        (struct gdt_entry){
                .base_0 = 0x0,
                .base_1 = 0x0,
                .base_2 = 0x0,
                .limit_0 = 0xffff,
                .limit_1 = 0xf,
                .accessed = false,
                .read_write = true,
                .dir_conform = false,
                .exec = false,
                .desc_type = true,
                .privelege = 0,
                .present = true,
                .long_mode_code = true,
                .protected_mode = false,
                .granularity = true,
        },
};

struct __attribute__((packed)) gdt_reg {
        uint16_t size;
        uint64_t offset;
};

void cpu_gdt_init_gdt(void)
{
        struct gdt_reg gdtr = {
                .size = sizeof(gdt),
                .offset = (uintptr_t)&gdt[0],
        };

        __asm__("cli\n"
                "lgdt %0\n"
                "mov %1, %%ax\n"
                "mov %%ax, %%ds\n"
                "mov %%ax, %%es\n"
                "mov %%ax, %%fs\n"
                "mov %%ax, %%gs\n"
                "mov %%ax, %%ss\n"
                "sti\n"
                :
                : "m" (gdtr), "i" (CPU_GDT_SELECTOR_KERNEL_DATA));
}
