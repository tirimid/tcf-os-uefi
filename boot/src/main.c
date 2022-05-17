#include <efi.h>
#include "io/file.h"
#include <efilib.h>
#include "boot/boot.h"
#include "io/text.h"
#include "io/ftype.h"

EFI_STATUS efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        boot_init(sys_table);
        
        EFI_FILE_HANDLE vol = file_image_volume(img_handle);
        EFI_FILE_HANDLE file = file_open(vol, L"sys\\kernel.elf");

        void *k_entry = ftype_load_elf(file, FTYPE_ELF_HEADER_INST_SET_X86_64,
                                       FTYPE_ELF_HEADER_TYPE_EXECUTABLE);

        file_close(file);

        __attribute__((ms_abi)) int (*k_main)(const struct boot_info *)
                = (int (*)(const struct boot_info *))k_entry;

        struct boot_info binfo = boot_info(img_handle);

        text_log_info(L"entering kernel...");
        boot_exit(img_handle);
        k_main(&binfo);
        
        return EFI_SUCCESS;
}
