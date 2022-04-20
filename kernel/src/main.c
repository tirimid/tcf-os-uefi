#include <efi.h>
#include <efilib.h>
#include <stdbool.h>

static inline bool
key_ready(EFI_SYSTEM_TABLE *st, EFI_INPUT_KEY *key)
{
        return st->ConIn->ReadKeyStroke(st->ConIn, key) != EFI_NOT_READY;
}

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        sys_table->ConOut->OutputString(sys_table->ConOut, L"hi world\r\n");
        sys_table->ConIn->Reset(sys_table->ConIn, false);
        EFI_INPUT_KEY key;
        while (!key_ready(sys_table, &key))
                continue;
        return EFI_SUCCESS;
}
