#ifndef _KERN_ERROR_H_
#define _KERN_ERROR_H_

enum error_panic_code {
        ERROR_PANIC_CODE_VITAL_INIT_FAIL = 0,
        ERROR_PANIC_CODE_MEMORY_FAIL = 1,
        ERROR_PANIC_CODE_UNRECOVERABLE_DOUBLE_FAULT = 2,
};

__attribute__((no_caller_saved_registers)) void error_panic(enum error_panic_code code,
                                                            const char *msg);

#endif
