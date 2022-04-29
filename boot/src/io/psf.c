#include "io/psf.h"

#include "io/files.h"
#include <stdbool.h>
#include "io/text.h"
#include "mem/pool.h"
#include <stddef.h>

#define FONT_HEADER_MAGIC 0x864ab572

static inline bool
is_font_header_valid(const struct psf_font_header *hdr)
{
        /* the <= 8 thing can be changed later when i add support for it in the
         * kernel psf font rendering
         */
        return hdr->magic == FONT_HEADER_MAGIC && hdr->width <= 8;
}

/* buffer of psf font must be freed after use */
struct psf_font
read_psf_font(EFI_FILE_HANDLE font_file)
{
        struct psf_font font;
        read_file(font_file, &font, 0, sizeof(font.hdr));
        if (!is_font_header_valid(&font.hdr))
                log_error(L"read_psf_font(): read invalid font header");
        size_t glyph_buf_size = font.hdr.glyph_bytes * font.hdr.glyph_cnt;
        font.glyph_buf = alloc_pool_mem(glyph_buf_size);
        read_file(font_file, font.glyph_buf, sizeof(font.hdr), glyph_buf_size);
        return font;
}
