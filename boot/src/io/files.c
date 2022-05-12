#include "io/files.h"

#include <efi.h>
#include <efilib.h>
#include "lcstring.h"

#define FILE_INFO_BUF_SIZE 128

EFI_FILE_HANDLE io_files_image_volume(EFI_HANDLE img_handle)
{
        EFI_LOADED_IMAGE *loaded_img;
        EFI_GUID lip_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;

        BS->HandleProtocol(img_handle, &lip_guid, (void **)&loaded_img);
        
        EFI_GUID fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
        EFI_FILE_IO_INTERFACE *vol_iface;
        
        BS->HandleProtocol(loaded_img->DeviceHandle, &fs_guid, (void **)&vol_iface);
        
        EFI_FILE_HANDLE vol;
        
        vol_iface->OpenVolume(vol_iface, &vol);
        
        return vol;
}

/* buffer is used to allow const file_name argument */
static wchar_t file_name_buf[256] = { L'\0' };

EFI_FILE_HANDLE io_files_open_file(EFI_FILE_HANDLE vol, const wchar_t *file_name)
{
        wcscpy(file_name_buf, file_name);
        
        EFI_FILE_HANDLE file;
        
        vol->Open(vol, &file, file_name_buf, EFI_FILE_MODE_READ,
                  EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
        
        return file;
}

void io_files_close_file(EFI_FILE_HANDLE file)
{
        file->Close(file);
}

void *io_files_read_file(EFI_FILE_HANDLE file, void *dst, uintptr_t offset, size_t size)
{
        file->SetPosition(file, offset);
        file->Read(file, &size, dst);

        return dst;
}

/* file info is read into a very large buffer to ensure enough size */
static uint8_t file_info_buf[FILE_INFO_BUF_SIZE];

size_t io_files_file_size(EFI_FILE_HANDLE file)
{
        EFI_FILE_INFO *info = (EFI_FILE_INFO *)file_info_buf;
        size_t buf_size = FILE_INFO_BUF_SIZE;

        file->GetInfo(file, &GenericFileInfo, &buf_size, info);
        
        return info->FileSize;
}
