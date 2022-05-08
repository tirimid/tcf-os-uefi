#include "mem/pool.h"

#include <efi.h>
#include <efilib.h>

void *alloc_pool_mem(size_t size)
{
        void *buf;
        EFI_STATUS rc = BS->AllocatePool(PoolAllocationType, size, &buf);
        
        return EFI_ERROR(rc) ? NULL : buf;
}

void free_pool_mem(void *buf)
{
        BS->FreePool(buf);
}
