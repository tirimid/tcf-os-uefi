#include "mem/paging.h"

#include <efi.h>
#include <efilib.h>

void *
alloc_page(void *phys_addr)
{
        return alloc_pages(phys_addr, 1);
}

void *
alloc_pages(void *phys_addr, size_t cnt)
{
        BS->AllocatePages(AllocateAddress, EfiLoaderData, cnt,
                          (EFI_PHYSICAL_ADDRESS *)&phys_addr);
                          
        return phys_addr;
}
