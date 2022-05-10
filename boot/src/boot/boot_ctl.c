#include "boot.h"

#include "io.h"
#include <efi.h>
#include <efilib.h>
#include "mem.h"

void boot_ctl_init_boot(EFI_SYSTEM_TABLE *sys_table)
{
        ST = sys_table;
        BS = sys_table->BootServices;
        
        io_text_log_info(L"initializing bootloader...");
}

void boot_ctl_exit_boot(EFI_HANDLE img_handle)
{
        io_text_log_info(L"exiting boot services...");
        BS->ExitBootServices(img_handle, 0);
}

struct com_boot_boot_info boot_ctl_boot_info(EFI_HANDLE img_handle)
{
        EFI_FILE_HANDLE vol = io_files_image_volume(img_handle);
        EFI_FILE_HANDLE font_file = io_files_open_file(vol, L"sys\\tamsyn-8x16-bold.psf");
        EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
        EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

        if (EFI_ERROR(BS->LocateProtocol(&gop_guid, NULL, (void **)&gop)))
                io_text_log_error(L"could not locate gop");
        
        return (struct com_boot_boot_info){
                .frame_buf = {
                        .base = (void *)gop->Mode->FrameBufferBase,
                        .size = gop->Mode->FrameBufferSize,
                        .res_horiz = gop->Mode->Info->HorizontalResolution,
                        .res_vert = gop->Mode->Info->VerticalResolution,
                        .scanline_pixels = gop->Mode->Info->PixelsPerScanLine,
                },
                .font = io_ftype_read_psf_font_file(font_file),
                .page_size = PAGE_SIZE,
        };
}
