#include "mem.h"

#include <efi.h>
#include <efilib.h>

void *
alloc_page(void *phys_addr)
{
        BS->AllocatePages(AllocateAddress, EfiLoaderData, 1,
                          (EFI_PHYSICAL_ADDRESS *)&phys_addr);
        return phys_addr;
}

void *
alloc_pages(void *phys_addr, size_t cnt)
{
        BS->AllocatePages(AllocateAddress, EfiLoaderData, cnt,
                          (EFI_PHYSICAL_ADDRESS *)&phys_addr);
        return phys_addr;
}

void
free_page(const void *page)
{
}

void
free_pages(const void *page, size_t cnt)
{
}

void *
alloc_pool_mem(size_t size)
{
        void *buf;
        EFI_STATUS rc = BS->AllocatePool(PoolAllocationType, size, &buf);
        return EFI_ERROR(rc) ? NULL : buf;
}

void
free_pool_mem(void *buf)
{
        BS->FreePool(buf);
}
