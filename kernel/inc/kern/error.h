#ifndef KERNEL_KERN_ERROR_H
#define KERNEL_KERN_ERROR_H

enum kern_error_panic_code {
        KERN_ERROR_PANIC_CODE_VITAL_INIT_FAIL = 0,
        KERN_ERROR_PANIC_CODE_MEMORY_FAIL = 1,
        KERN_ERROR_PANIC_CODE_UNRECOVERABLE_DOUBLE_FAULT = 2,
};

__attribute__((no_caller_saved_registers)) void kern_error_panic(enum kern_error_panic_code code,
                                                                 const char *msg);

#endif
