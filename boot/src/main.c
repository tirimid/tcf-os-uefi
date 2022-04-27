#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io/files.h"
#include "io/text.h"
#include "load/elf.h"

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        EFI_FILE_HANDLE vol = image_volume(img_handle);
        EFI_FILE_HANDLE file = open_file(vol, L"sys\\tcf-kernel.elf");
        void *kernel_entry = load_elf_file(file, ELF_HEADER_INST_SET_X86_64,
                                           ELF_HEADER_TYPE_EXECUTABLE);
        int (*kernel_main)(void) = (int (*)(void))kernel_entry;
        close_file(file);
        log_info(L"entering kernel...");
        kernel_main();
        log_error(L"leaving kernel...");
        return EFI_SUCCESS;
}
