#include "mem/pool.h"

#include <efi.h>
#include <efilib.h>

void *pool_alloc(size_t size)
{
        void *buf;
        EFI_STATUS rc = BS->AllocatePool(PoolAllocationType, size, &buf);
        
        return EFI_ERROR(rc) ? NULL : buf;
}

void pool_free(void *buf)
{
        BS->FreePool(buf);
}
