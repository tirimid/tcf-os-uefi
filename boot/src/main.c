#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io/files.h"
#include "io/text.h"

static wchar_t test[256] = { L'\0' };

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        EFI_FILE_HANDLE vol = get_image_volume(img_handle);
        EFI_FILE_HANDLE file = open_file(vol, L"uefi\\test.txt");
        read_file(file, test, 106);
        print(test);
        print_line(L";");
        close_file(file);
        log_error(L"error time");
        return EFI_SUCCESS;
}
