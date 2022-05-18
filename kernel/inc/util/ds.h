#ifndef UTIL_DS_H__
#define UTIL_DS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct ds_bitmap {
        uint8_t *data;
        size_t size_bits;
};

bool ds_bitmap_bit(const struct ds_bitmap *bm, size_t ind);
void ds_set_bitmap_bit(struct ds_bitmap *bm, size_t ind, bool state);
size_t ds_bitmap_size_bytes(const struct ds_bitmap *bm);

#endif
