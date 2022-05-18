#ifndef KERN_KERN_H__
#define KERN_KERN_H__

#include "common/boot.h"

void kern_init(const struct boot_info *info);

void kern_hang(void);

#endif
