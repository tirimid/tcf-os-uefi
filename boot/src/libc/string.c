#include "libc/string.h"

void *
memset(void *dst, uint8_t b, size_t size)
{
        for (size_t i = 0; i < size; ++i)
                *((uint8_t *)dst + i) = b;
        return dst;
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
memcmp(const uint8_t *restrict a, const uint8_t *restrict b, size_t size)
{
        for (size_t i = 0; i < size; ++i) {
                if (*u_a > *u_b)
                        return 1;
                else if (*u_a < *u_b)
                        return -1;
        }
}
