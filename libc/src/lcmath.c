#include "lcmath.h"

int ceil(float n)
{
        if (n > 0)
                return n - (int)n > 0 ? (int)(n + 1) : (int)n;
        else
                return n - (int)n < 0 ? (int)(n - 1) : (int)n;
}
