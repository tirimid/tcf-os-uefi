#include "boot.h"

#include "defs.h"
#include "io/text.h"
#include "mem/paging.h"
#include "io/files.h"
#include "io/rdftype.h"

void init_boot(EFI_SYSTEM_TABLE *sys_table)
{
        ST = sys_table;
        BS = sys_table->BootServices;
        
        log_info(L"initializing bootloader...");
}

void exit_boot(EFI_HANDLE img_handle)
{
        log_info(L"exiting boot services...");
        BS->ExitBootServices(img_handle, 0);
}

struct boot_info retrieve_boot_info(EFI_HANDLE img_handle)
{
        EFI_FILE_HANDLE vol = image_volume(img_handle);
        EFI_FILE_HANDLE font_file = open_file(vol,
                                              L"sys\\tamsyn-8x16-bold.psf");
        
        EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
        EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

        if (EFI_ERROR(BS->LocateProtocol(&gop_guid, NULL, (void **)&gop)))
                log_error(L"current_frame_buf(): could not locate gop");
        
        return (struct boot_info){
                .frame_buf = {
                        .base = (void *)gop->Mode->FrameBufferBase,
                        .size = gop->Mode->FrameBufferSize,
                        .res_horiz = gop->Mode->Info->HorizontalResolution,
                        .res_vert = gop->Mode->Info->VerticalResolution,
                        .scanline_pixels = gop->Mode->Info->PixelsPerScanLine,
                },
                .font = read_psf_font_file(font_file),
                .page_size = PAGE_SIZE,
        };
}
