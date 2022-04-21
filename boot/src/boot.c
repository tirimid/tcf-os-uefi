#include "boot.h"

#include "io/text.h"
#include "defs.h"

void
init_boot(EFI_SYSTEM_TABLE *sys_table)
{
        ST = sys_table;
        print(L"tcf-boot-uefi ");
        print_line(boot_version());
        log_info(L"initializing bootloader...");
        log_error(L"error time");
}

const wchar_t *
boot_version(void)
{
        return VERSION(0, 21, 4, 22);
}
