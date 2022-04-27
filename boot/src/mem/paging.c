#include "mem/paging.h"

#include <efi.h>
#include <efilib.h>

void *
alloc_page(void *phys_addr)
{
        void *ptr = phys_addr;
        BS->AllocatePages(AllocateAddress, EfiLoaderData, 1,
                          (EFI_PHYSICAL_ADDRESS *)&ptr);
        return ptr;
}

void *
alloc_pages(void *phys_addr, size_t cnt)
{
        void *ptr = phys_addr;
        BS->AllocatePages(AllocateAddress, EfiLoaderData, cnt,
                          (EFI_PHYSICAL_ADDRESS *)&ptr);
        return ptr;
}

void
free_page(const void *page)
{
}

void
free_pages(const void *page, size_t cnt)
{
}
