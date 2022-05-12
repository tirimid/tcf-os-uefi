#ifndef KERNEL_H_a6HHAJp7q8Drsi5aK3WEJLEc80lXd8io
#define KERNEL_H_a6HHAJp7q8Drsi5aK3WEJLEc80lXd8io

#include "common.h"

/* ==========
 * kern_ctl.c
 * ==========
 */

void kern_ctl_init(struct com_boot_info *info);
void kern_ctl_hang(void);

#endif
