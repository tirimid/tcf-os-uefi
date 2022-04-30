#ifndef UTIL_H_rdEI69gHLeYOXqSot93l9oiPtarHhh3J
#define UTIL_H_rdEI69gHLeYOXqSot93l9oiPtarHhh3J

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct bitmap {
        uint8_t *data;
        size_t size_bits;
};

bool
bitmap_bit(const struct bitmap *bm, size_t ind);

void
set_bitmap_bit(struct bitmap *bm, size_t ind, bool state);

#endif
