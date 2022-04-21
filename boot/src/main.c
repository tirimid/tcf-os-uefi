#include <efi.h>
#include <efilib.h>
#include "boot.h"

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        return EFI_SUCCESS;
}
