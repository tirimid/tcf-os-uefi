#ifndef KERNEL_H_a6HHAJp7q8Drsi5aK3WEJLEc80lXd8io
#define KERNEL_H_a6HHAJp7q8Drsi5aK3WEJLEc80lXd8io

#include "comboot.h"

void
init_kernel(const struct boot_info *info);

void
hang(void);

#endif
