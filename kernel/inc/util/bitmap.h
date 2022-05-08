#ifndef BITMAP_H_M8ZrotvBtPFzMcJ7gwhDpYWZKFkxkYA6
#define BITMAP_H_M8ZrotvBtPFzMcJ7gwhDpYWZKFkxkYA6

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct bitmap {
        uint8_t *data;
        size_t size_bits;
};

bool bitmap_bit(const struct bitmap *bm, size_t ind);
void set_bitmap_bit(struct bitmap *bm, size_t ind, bool state);
size_t bitmap_size_bytes(const struct bitmap *bm);

#endif
