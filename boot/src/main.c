#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io/files.h"
#include "io/text.h"
#include "load/elf.h"

void *
load_kernel(EFI_HANDLE img_handle)
{
        EFI_FILE_HANDLE vol = image_volume(img_handle);
        EFI_FILE_HANDLE file = open_file(vol, L"sys\\kernel.elf");
        void *kernel_entry = load_elf_file(file, ELF_HEADER_INST_SET_X86_64,
                                           ELF_HEADER_TYPE_EXECUTABLE);
        close_file(file);
        return kernel_entry;
}

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        log_info(L"entering kernel...");
        __attribute__((ms_abi)) int (*kernel_entry)(const struct boot_info *)
                = (int (*)(const struct boot_info *))load_kernel(img_handle);
        struct boot_info boot_info = retrieve_boot_info(img_handle);
        exit_boot(img_handle);
        kernel_entry(&boot_info);
        return EFI_SUCCESS;
}
