#include "string.h"

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
void
fast_memset(void *dst, uint64_t q, size_t writes)
{
        __asm__("mov %0, %%rdi\n"
                "mov %1, %%rcx\n"
                "mov %2, %%rax\n"
                "rep stosq\n"
                :
                : "m" (dst), "m" (writes), "m" (q)
                : "rcx");
}

void
memcpy(void *restrict dst, const void *restrict src, size_t size)
{
        for (size_t i = 0; i < size; ++i)
                *((uint8_t *restrict)dst + i) = *((uint8_t *restrict)src + i);
}

wchar_t *
wcscpy(wchar_t *restrict dst, const wchar_t *restrict src)
{
        int i = 0;
        for (; src[i] != L'\0'; ++i)
                dst[i] = src[i];
        dst[i] = L'\0';
        return dst;
}

int
memcmp(const void *a, const void *b, size_t size)
{
        for (size_t i = 0; i < size; ++i) {
                if (*((const uint8_t *)a + i) > *((const uint8_t *)b + i))
                        return 1;
                else if (*((const uint8_t *)a + i) < *((const uint8_t *)b + i))
                        return -1;
        }
        return 0;
}
