#include "mem/page.h"

void *mem_page_alloc_page(void *phys_addr)
{
        return mem_page_alloc_pages(phys_addr, 1);
}

void *mem_page_alloc_pages(void *phys_addr, size_t cnt)
{
        BS->AllocatePages(AllocateAddress, EfiLoaderData, cnt, (EFI_PHYSICAL_ADDRESS *)&phys_addr);
                          
        return phys_addr;
}
