#include <efi.h>
#include <efilib.h>

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        InitializeLib(img_handle, sys_table);
        Print(L"hello world");
        return EFI_SUCCESS;
}
