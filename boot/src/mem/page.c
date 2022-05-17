#include "mem/page.h"

void *page_alloc(void *phys_addr, size_t page_cnt)
{
        BS->AllocatePages(AllocateAddress, EfiLoaderData, page_cnt,
                          (EFI_PHYSICAL_ADDRESS *)&phys_addr);
                          
        return phys_addr;
}
