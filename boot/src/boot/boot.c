#include "boot/boot.h"

#include "io/text.h"
#include "io/file.h"
#include "mem/mmap.h"
#include "mem/page.h"
#include <stdbool.h>
#include "io/ftype.h"

void boot_init(EFI_SYSTEM_TABLE *sys_table)
{
        static bool initialized = false;

        if (initialized)
                return;

        ST = sys_table;
        BS = sys_table->BootServices;
        
        text_log_info(L"initializing bootloader...");

        initialized = true;
}

void boot_exit(EFI_HANDLE img_handle)
{
        text_log_info(L"exiting boot services...");
        BS->ExitBootServices(img_handle, 0);
}

struct boot_info boot_info(EFI_HANDLE img_handle)
{
        EFI_FILE_HANDLE vol = file_image_volume(img_handle);
        EFI_FILE_HANDLE font_file = file_open(vol, L"sys\\tamsyn-8x16-bold.psf");
        EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
        EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

        if (EFI_ERROR(BS->LocateProtocol(&gop_guid, NULL, (void **)&gop)))
                text_log_error(L"could not locate gop");
        
        return (struct boot_info){
                .frame_buf = {
                        .base = (void *)gop->Mode->FrameBufferBase,
                        .size = gop->Mode->FrameBufferSize,
                        .res_horiz = gop->Mode->Info->HorizontalResolution,
                        .res_vert = gop->Mode->Info->VerticalResolution,
                        .scanline_pixels = gop->Mode->Info->PixelsPerScanLine,
                },
                .font = ftype_read_psf_font(font_file),
                .mem_map = mmap_get(),
                .page_size = PAGE_SIZE,
        };
}
