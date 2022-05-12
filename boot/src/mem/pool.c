#include "mem/pool.h"

#include <efi.h>
#include <efilib.h>

void *mem_pool_alloc_mem(size_t size)
{
        void *buf;
        EFI_STATUS rc = BS->AllocatePool(PoolAllocationType, size, &buf);
        
        return EFI_ERROR(rc) ? NULL : buf;
}

void mem_pool_free_mem(void *buf)
{
        BS->FreePool(buf);
}
