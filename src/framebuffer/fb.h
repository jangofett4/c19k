#ifndef __C19K_FB_H__
#define __C19K_FB_H__

#include <stdbool.h>
#include "../limine.h"

#define FB_RGBA(r, g, b, a) b | ((uint32_t)g) << 8 | ((uint32_t)r) << 16 | ((uint32_t)a) << 24
#define FB_RGB(r, g, b) b | ((uint32_t)g) << 8 | ((uint32_t)r) << 16 | 255 << 24

static const uint32_t FB_BLACK_PIXEL    = 0x00000000;
static const uint32_t FB_WHITE_PIXEL    = 0xFFFFFFFF;
static const uint32_t FB_RED_PIXEL      = FB_RGB(255, 0, 0);
static const uint32_t FB_GREEN_PIXEL    = FB_RGB(0, 255, 0);
static const uint32_t FB_BLUE_PIXEL     = FB_RGB(0, 0, 255);

bool fb_check(uint64_t fbnr);
uint64_t fb_height(uint64_t fbnr);
uint64_t fb_width(uint64_t fbnr);

struct limine_framebuffer* fb_get(uint64_t fbnr);
uint32_t* fb_get_buffer(uint64_t fbnr);

void fb_putpixel(uint64_t fbnr, uint32_t x, uint32_t y, uint32_t color);

#endif
