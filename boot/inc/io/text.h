#ifndef _IO_TEXT_H_
#define _IO_TEXT_H_

#include <stddef.h>

void text_print(const wchar_t *s);
void text_print_line(const wchar_t *s);

void text_log_info(const wchar_t *s);
void text_log_warning(const wchar_t *s);
void text_log_error(const wchar_t *s);

#endif
