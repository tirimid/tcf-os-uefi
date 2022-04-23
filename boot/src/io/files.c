#include "io/files.h"

#include "libc/string.h"

#define FILE_NAME_BUF_SIZE 256

EFI_FILE_HANDLE
get_image_volume(EFI_HANDLE img_handle)
{
        EFI_LOADED_IMAGE *loaded_img;
        EFI_GUID lip_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
        BS->HandleProtocol(img_handle, &lip_guid, (void **)&loaded_img);
        EFI_GUID fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
        EFI_FILE_IO_INTERFACE *vol_iface;
        BS->HandleProtocol(loaded_img->DeviceHandle, &fs_guid,
                           (void **)&vol_iface);
        EFI_FILE_HANDLE vol;
        vol_iface->OpenVolume(vol_iface, &vol);
        return vol;
}

static wchar_t file_name_buf[FILE_NAME_BUF_SIZE] = { L'\0' };

EFI_FILE_HANDLE
open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name)
{
        wcscpy(file_name_buf, file_name); /* buffer is used to allow const
                                           * file_name argument
                                           */
        EFI_FILE_HANDLE file;
        vol->Open(vol, &file, file_name_buf, EFI_FILE_MODE_READ,
                  EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
        return file;
}

void
read_file(EFI_FILE_HANDLE file, void *dst, size_t size)
{
        file->Read(file, &size, dst);
}

void
close_file(EFI_FILE_HANDLE file)
{
        file->Close(file);
}
