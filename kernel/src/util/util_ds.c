#include "util.h"

#include "lcmath.h"

bool util_ds_bitmap_bit(const struct util_ds_bitmap *bm, size_t ind)
{
        size_t byte = ind / 8;
        size_t bit = ind % 8;
        uint8_t mask = 1 << bit;

        return (bm->data[byte] & mask) > 0;
}

void util_ds_set_bitmap_bit(struct util_ds_bitmap *bm, size_t ind, bool state)
{
        size_t byte = ind / 8;
        size_t bit = ind % 8;
        uint8_t mask = 1 << bit;
        
        bm->data[byte] &= ~mask;
        
        if (state)
                bm->data[byte] |= mask;
}

size_t util_ds_bitmap_size_bytes(const struct util_ds_bitmap *bm)
{
        return ceil((float)bm->size_bits / 8.0f);
}
