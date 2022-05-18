#ifndef IO_TEXT_H__
#define IO_TEXT_H__

#include <stddef.h>

void text_print(const wchar_t *s);
void text_print_line(const wchar_t *s);

void text_log_info(const wchar_t *s);
void text_log_warning(const wchar_t *s);
void text_log_error(const wchar_t *s);

#endif
