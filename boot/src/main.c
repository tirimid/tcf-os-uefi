#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io/files.h"
#include "io/text.h"
#include "mem/pool.h"

static void
print_file_conts(EFI_HANDLE img_handle, const wchar_t *file_name)
{
        EFI_FILE_HANDLE vol = get_image_volume(img_handle);
        EFI_FILE_HANDLE file = open_file(vol, file_name);
        wchar_t *file_buf = alloc_pool_mem(file_size(file));
        read_file(file, file_buf, file_size(file));
        print_line(file_buf);
        free_pool_mem(file_buf);
        close_file(file);
}

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        print_file_conts(img_handle, L"uefi\\test.txt");
        log_error(L"success, hanging program");
        return EFI_SUCCESS;
}
