#include "gfx.h"

#include <efi.h>
#include "io.h"
#include <efilib.h>

struct frame_buf
current_frame_buf(void)
{
        EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
        EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
        if (EFI_ERROR(BS->LocateProtocol(&gop_guid, NULL, (void **)&gop)))
                log_error(L"current_frame_buf(): could not locate gop");
        return (struct frame_buf){
                .base = (void *)gop->Mode->FrameBufferBase,
                .size = gop->Mode->FrameBufferSize,
                .res_horiz = gop->Mode->Info->HorizontalResolution,
                .res_vert = gop->Mode->Info->VerticalResolution,
                .scanline_pixels = gop->Mode->Info->PixelsPerScanLine,
        };
}
