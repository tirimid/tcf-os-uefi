#ifndef STRING_H_Fsl928jxSCfKpQr6ioBiZ6CQhlM9Wqaz
#define STRING_H_Fsl928jxSCfKpQr6ioBiZ6CQhlM9Wqaz

#include <stddef.h>
#include <stdint.h>

void *
memset(void *dst, uint8_t b, size_t size);

wchar_t *
wcscpy(wchar_t *restrict dst, const wchar_t *restrict src);

int
memcmp(const uint8_t *restrict a, const uint8_t *restrict b, size_t size);

#endif
