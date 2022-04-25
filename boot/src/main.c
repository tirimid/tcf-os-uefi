#include <efi.h>
#include <efilib.h>
#include "boot.h"
#include "io/files.h"
#include "io/text.h"
#include "mem/pool.h"
#include "load/elf.h"

static void
test_elf_file(EFI_HANDLE img_handle, const wchar_t *file_name)
{
        EFI_FILE_HANDLE vol = get_image_volume(img_handle);
        EFI_FILE_HANDLE file = open_file(vol, file_name);
        wchar_t *file_buf = alloc_pool_mem(file_size(file));
        read_file(file, file_buf, file_size(file));
        const struct elf_header *hdr = (const struct elf_header *)file_buf;
        if (hdr->inst_set == ELF_HEADER_INST_SET_X86_64)
                log_info(L"x86-64 elf file");
        free_pool_mem(file_buf);
        close_file(file);
}

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *sys_table)
{
        init_boot(sys_table);
        test_elf_file(img_handle, L"sys\\tcf-kernel.elf");
        log_error(L"success, hanging program");
        return EFI_SUCCESS;
}
