#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io/text.h"
#include "io/rdftype.h"
#include "io/files.h"

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        log_info(L"entering kernel...");
        
        EFI_FILE_HANDLE vol = image_volume(img_handle);
        EFI_FILE_HANDLE file = open_file(vol, L"sys\\kernel.elf");

        void *kernel_entry = load_elf_file(file, ELF_HEADER_INST_SET_X86_64,
                                           ELF_HEADER_TYPE_EXECUTABLE);

        close_file(file);

        __attribute__((ms_abi)) int (*kernel_main)(const struct boot_info *)
                = (int (*)(const struct boot_info *))kernel_entry;

        struct boot_info boot_info = retrieve_boot_info(img_handle);

        exit_boot(img_handle);
        kernel_main(&boot_info);
        
        return EFI_SUCCESS;
}
