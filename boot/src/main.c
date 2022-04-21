#include <efi.h>
#include <efilib.h>
#include "io/text.h"

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        ST = sys_table;
        log_info(L"hello world");
        log_error(L"testing an error message");
        return EFI_SUCCESS;
}
