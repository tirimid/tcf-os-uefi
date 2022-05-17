#include "io/text.h"

#include <efi.h>
#include <efilib.h>
#include <stdbool.h>
#include "lcstring.h"

#define LOG_PREFIX L"[ tcf-boot ]"

/* allow const string as argument in function */
static wchar_t print_buf[512] = { L'\0' };

void text_print(const wchar_t *s)
{
        wcscpy(print_buf, s);
        ST->ConOut->OutputString(ST->ConOut, print_buf);
}

void text_print_line(const wchar_t *s)
{
        text_print(s);
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
}

void text_log_info(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" info: ");
        text_print_line(s);
}

void text_log_warning(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" warning: ");
        text_print_line(s);
}

void text_log_error(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" error: ");
        text_print_line(s);

        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
