#ifndef KERNEL_KERN_CTL_H
#define KERNEL_KERN_CTL_H

#include "comboot.h"

void kern_ctl_init(const struct com_boot_info *info);

void kern_ctl_hang(void);

#endif
