#ifndef TEXT_H_EpgG9lEHm8lSJHHe51etGEGQSTQCC00e
#define TEXT_H_EpgG9lEHm8lSJHHe51etGEGQSTQCC00e

#include <efi.h>
#include <efilib.h>
#include <stddef.h>

void
print(const wchar_t *s);

void
print_line(const wchar_t *s);

void
log_info(const wchar_t *s);

void
log_error(const wchar_t *s);

#endif
