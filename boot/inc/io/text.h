#ifndef BOOT_IO_TEXT_H
#define BOOT_IO_TEXT_H

#include <stddef.h>

void io_text_print(const wchar_t *s);
void io_text_print_line(const wchar_t *s);

void io_text_log_info(const wchar_t *s);
void io_text_log_warning(const wchar_t *s);
void io_text_log_error(const wchar_t *s);

#endif
