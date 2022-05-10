OUTPUT_FORMAT(elf64-x86-64)
ENTRY(main)

SECTIONS
{
        __KERNEL_ELF_START__ = .;
        
        .text : ALIGN(0x1000) {
                *(.text)
        }
        
        .data : ALIGN(0x1000) {
                *(.data)
        }
        
        .rodata : ALIGN(0x1000) {
                *(.rodata)
        }

        .bss : ALIGN(0x1000) {
                *(COMMON)
                *(.bss)
        }
        
        __KERNEL_ELF_END__ = .;
}
