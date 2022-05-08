#include "util/bitmap.h"

bool bitmap_bit(const struct bitmap *bm, size_t ind)
{
        size_t byte = ind / 8;
        size_t bit = ind % 8;
        uint8_t mask = 1 << bit;

        return (bm->data[byte] & mask) > 0;
}

void set_bitmap_bit(struct bitmap *bm, size_t ind, bool state)
{
        size_t byte = ind / 8;
        size_t bit = ind % 8;
        uint8_t mask = 1 << bit;
        
        bm->data[byte] &= ~mask;
        
        if (state)
                bm->data[byte] |= mask;
}

size_t bitmap_size_bytes(const struct bitmap *bm)
{
        return ceil((float)bm->size_bits / 8.0f);
}
