#include "libc/string.h"

void *
memset(void *dst, uint8_t b, size_t size)
{
        for (size_t i = 0; i < size; ++i)
                *((uint8_t *)dst + i) = b;        
        return dst;
}

/* same as memset but 8 bytes are set at a time, instead of 1 - notably
 * increasing performance
 */
void *
fast_memset(void *dst, uint64_t q, size_t writes)
{
        __asm__("mov %0, %%rdi\n"
                "mov %1, %%rcx\n"
                "mov %2, %%rax\n"
                "rep stosq\n"
                :
                : "m" (dst), "m" (writes), "m" (q)
                : "rcx");
        return dst;
}

void *
memcpy(void *restrict dst, const void *restrict src, size_t size)
{
        for (int i = 0; i < size; ++i)
                *((uint8_t *)dst + i) = *((const uint8_t *)src + i);
        return dst;
}
