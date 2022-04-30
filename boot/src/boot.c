#include "boot.h"

#include "defs.h"
#include "io.h"
#include "gfx.h"

void
init_boot(EFI_SYSTEM_TABLE *sys_table)
{
        ST = sys_table;
        BS = sys_table->BootServices;
        
        print(L"tcf-boot-uefi ");
        print_line(boot_version());
        log_info(L"initializing bootloader...");
}

const wchar_t *
boot_version(void)
{
        return VERSION(0, 29, 4, 22);
}

void
exit_boot(EFI_HANDLE img_handle)
{
        log_info(L"exiting boot services...");
        BS->ExitBootServices(img_handle, 0);
}

struct boot_info
retrieve_boot_info(EFI_HANDLE img_handle)
{
        EFI_FILE_HANDLE vol = image_volume(img_handle);
        EFI_FILE_HANDLE font_file = open_file(vol,
                                              L"sys\\tamsyn-8x16-bold.psf");
        
        return (struct boot_info){
                .frame_buf = current_frame_buf(),
                .font = read_psf_font_file(font_file),
        };
}
