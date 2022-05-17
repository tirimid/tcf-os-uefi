#include "cpu/io.h"

/* wait for slow io port operations to finish */
static inline void wait_port_io(void)
{
        __asm__("outl %0, $0x80\n"
                :
                : "a" (0));
}

void io_write_port_byte(enum io_port port, uint8_t b)
{
        __asm__("outb %0, %1\n"
                :
                : "a" (b), "Nd" ((uint16_t)port));
        
        wait_port_io();
}

void io_write_port_word(enum io_port port, uint16_t w)
{
        __asm__("outw %0, %1\n"
                :
                : "a" (w), "Nd" ((uint16_t)port));
        
        wait_port_io();
}

void io_write_port_long(enum io_port port, uint32_t l)
{
        __asm__("outl %0, %1\n"
                :
                : "a" (l), "Nd" ((uint16_t)port));

        wait_port_io();
}

__attribute__((no_caller_saved_registers)) uint8_t io_read_port_byte(enum io_port port)
{
        uint8_t b;

        __asm__("inb %1, %0\n"
                : "=a" (b)
                : "Nd" ((uint16_t)port));
        
        wait_port_io();

        return b;
}

uint16_t io_read_port_word(enum io_port port)
{
        uint16_t w;

        __asm__("inw %1, %0\n"
                : "=a" (w)
                : "Nd" ((uint16_t)port));
        
        wait_port_io();

        return w;
}

uint32_t io_read_port_long(enum io_port port)
{
        uint32_t l;

        __asm__("inl %1, %0\n"
                : "=a" (l)
                : "Nd" ((uint16_t)port));
        
        wait_port_io();

        return l;
}
