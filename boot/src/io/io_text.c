#include "io.h"

#include <stdbool.h>
#include "lcstring.h"

#define LOG_PREFIX L"[ tcf-boot ] "

/* allow const string as argument in function */
static wchar_t print_buf[512] = { L'\0' };

void io_text_print(const wchar_t *s)
{
        wcscpy(print_buf, s);
        ST->ConOut->OutputString(ST->ConOut, print_buf);
}

void io_text_print_line(const wchar_t *s)
{
        io_text_print(s);
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
}

void io_text_log_info(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" info: ");
        io_text_print_line(s);
}

void io_text_log_warning(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" warning: ");
        io_text_print_line(s);
}

void io_text_log_error(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" error: ");
        io_text_print_line(s);

        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
