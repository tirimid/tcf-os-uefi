#ifndef UTIL_H_QxHt0aIAG6rEHJiOgQyt8hEvZrWN3JrR
#define UTIL_H_QxHt0aIAG6rEHJiOgQyt8hEvZrWN3JrR

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* =========
 * util_ds.c
 * =========
 */

struct util_ds_bitmap {
        uint8_t *data;
        size_t size_bits;
};

bool util_ds_bitmap_bit(const struct util_ds_bitmap *bm, size_t ind);
void util_ds_set_bitmap_bit(struct util_ds_bitmap *bm, size_t ind, bool state);
size_t util_ds_bitmap_size_bytes(const struct util_ds_bitmap *bm);

#endif
