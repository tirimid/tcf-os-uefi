#ifndef LCSTRING_H__
#define LCSTRING_H__

#include <stddef.h>
#include <stdint.h>

void *memset(void *dst, uint8_t b, size_t size);

/* same as memset but 8 bytes are set at a time, instead of 1 - notably increasing performance */
void fast_memset(void *dst, uint64_t q, size_t writes);

void memcpy(void *restrict dst, const void *restrict src, size_t size);
wchar_t *wcscpy(wchar_t *restrict dst, const wchar_t *restrict src);
int memcmp(const void *restrict a, const void *restrict b, size_t size);

size_t strlen(const char *s);

#endif
