#ifndef _KERN_KERN_H_
#define _KERN_KERN_H_

#include "common/boot.h"

void kern_init(const struct boot_info *info);

void kern_hang(void);

#endif
