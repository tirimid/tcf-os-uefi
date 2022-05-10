#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io.h"

EFI_STATUS efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        boot_ctl_init(sys_table);
        
        EFI_FILE_HANDLE vol = io_files_image_volume(img_handle);
        EFI_FILE_HANDLE file = io_files_open_file(vol, L"sys\\kernel.elf");

        void *k_entry = io_ftype_load_elf_file(file, ELF_HEADER_INST_SET_X86_64,
                                               ELF_HEADER_TYPE_EXECUTABLE);

        io_files_close_file(file);

        __attribute__((ms_abi)) int (*k_main)(const struct com_boot_info *)
                = (int (*)(const struct com_boot_info *))k_entry;

        struct com_boot_info boot_info = boot_ctl_info(img_handle);

        io_text_log_info(L"entering kernel...");
        boot_ctl_exit(img_handle);
        k_main(&boot_info);
        
        return EFI_SUCCESS;
}
