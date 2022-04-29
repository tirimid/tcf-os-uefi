#ifndef STRING_H_24SHUcD36eolWwEViciV1scgR3DqUSiW
#define STRING_H_24SHUcD36eolWwEViciV1scgR3DqUSiW

#include <stdint.h>
#include <stddef.h>

void *
memset(void *dst, uint8_t b, size_t size);

/* same as memset but 8 bytes are set at a time, instead of 1 - notably
 * increasing performance
 */
void
fast_memset(void *dst, uint64_t q, size_t writes);

#endif
