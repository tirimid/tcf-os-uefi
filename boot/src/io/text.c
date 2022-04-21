#include "io/text.h"

#include <stddef.h>
#include <stdbool.h>

#define LOG_PREFIX L"[ tcf-boot-uefi ]"

void
print(const wchar_t *s)
{
        ST->ConOut->OutputString(ST->ConOut, s);
}

void
print_line(const wchar_t *s)
{
        print(s);
        print(L"\r\n");
}

void
log_info(const wchar_t *s)
{
        print(LOG_PREFIX L" info: ");
        print_line(s);
}

void
log_error(const wchar_t *s)
{
        print(LOG_PREFIX L" error: ");
        print_line(s);
        while (true) {
                __asm__("cli\n"
                        "hlt\n");
        };
}
