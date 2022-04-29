#ifndef PSF_H_W1CE4OrxZJlZ8nVz1y4HCMqdFa8ZvVGp
#define PSF_H_W1CE4OrxZJlZ8nVz1y4HCMqdFa8ZvVGp

#include "gfxtypes.h"
#include <stddef.h>
#include <efi.h>
#include <efilib.h>

/* buffer of psf font must be freed after use */
struct psf_font
read_psf_font(EFI_FILE_HANDLE font_file);

#endif
