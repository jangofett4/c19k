#ifndef __C19K_FB_H__
#define __C19K_FB_H__

#include <stdbool.h>
#include "../limine.h"

#define FB_RGBA(r, g, b, a) b | ((uint32_t)g) << 8 | ((uint32_t)r) << 16 | ((uint32_t)a) << 24
#define FB_RGB(r, g, b) b | ((uint32_t)g) << 8 | ((uint32_t)r) << 16 | 255 << 24

struct RGBA
{
    union {
        struct {
            uint32_t r, g, b, a;
        };
        uint32_t rgba[4];
    };
};

class KernelFramebuffer
{
    uint32_t fbnr;

    uint64_t width, height;

    limine_framebuffer* fbptr;
    uint32_t* rawptr;
    
public:
    KernelFramebuffer(uint32_t fbnr);
    ~KernelFramebuffer();

    static bool Check(uint64_t fbnr);

    uint64_t GetWidth() const;
    uint64_t GetHeight() const;

    uint32_t* Raw() const;

    void PutPixel(uint32_t x, uint32_t y, uint32_t color);
};

static const uint32_t FB_BLACK_PIXEL    = 0x00000000;
static const uint32_t FB_WHITE_PIXEL    = 0xFFFFFFFF;
static const uint32_t FB_RED_PIXEL      = FB_RGB(255, 0, 0);
static const uint32_t FB_GREEN_PIXEL    = FB_RGB(0, 255, 0);
static const uint32_t FB_BLUE_PIXEL     = FB_RGB(0, 0, 255);

#endif
