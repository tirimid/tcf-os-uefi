#include "io/text.h"

#include <stddef.h>
#include <stdbool.h>
#include "libc/string.h"

#define LOG_PREFIX L"[ tcf-boot-uefi ]"
#define PRINT_BUF_SIZE 512

static wchar_t print_buf[PRINT_BUF_SIZE] = { L'\0' };

void
print(const wchar_t *s)
{
        wcscpy(print_buf, s); /* allow const string as argument in function */
        ST->ConOut->OutputString(ST->ConOut, print_buf);
}

void
print_line(const wchar_t *s)
{
        print(s);
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
}

void
log_info(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" info: ");
        print_line(s);
}

void
log_error(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, LOG_PREFIX L" error: ");
        print_line(s);
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        }
}
