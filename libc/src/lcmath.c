#include "lcmath.h"

int64_t ceil(double n)
{
        if (n > 0)
                return n - (int64_t)n > 0 ? (int64_t)(n + 1) : (int64_t)n;
        else
                return n - (int64_t)n < 0 ? (int64_t)(n - 1) : (int64_t)n;
}
