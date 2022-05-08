#include "io/text.h"

#include <stdbool.h>
#include "lcstring.h"

#define LOG_PREFIX L"[ tcf-boot ] "

/* allow const string as argument in function */
static wchar_t print_buf[512] = { L'\0' };

void print(const wchar_t *s)
{
        wcscpy(print_buf, s);
        ST->ConOut->OutputString(ST->ConOut, print_buf);
}

void print_line(const wchar_t *s)
{
        print(s);
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
}

void log_info(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" info: ");
        print_line(s);
}

void log_error(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" error: ");
        print_line(s);

        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
