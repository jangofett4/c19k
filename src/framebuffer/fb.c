#include "fb.h"

#include "../kernel.h"

#include "font8x8_basic.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

inline bool fb_check(uint64_t fbnr)
{
    return framebuffer_request.response && framebuffer_request.response->framebuffer_count > fbnr;
}

inline uint64_t fb_width(uint64_t fbnr) { return framebuffer_request.response->framebuffers[fbnr]->width; }
inline uint64_t fb_height(uint64_t fbnr) { return framebuffer_request.response->framebuffers[fbnr]->height; }

struct limine_framebuffer* fb_get(uint64_t fbnr)
{
    return framebuffer_request.response->framebuffers[fbnr];
}

void fb_putpixel(uint64_t fbnr, uint32_t x, uint32_t y, uint32_t color)
{
    uint64_t width = framebuffer_request.response->framebuffers[fbnr]->width;
    ((uint32_t*)framebuffer_request.response->framebuffers[fbnr]->address)[width * y + x] = color;
}

void fb_putchar(uint64_t fbnr, uint32_t x, uint32_t y, char c, uint32_t color)
{
    char* data = font8x8_basic[c];
    for (int i = 0; i < 8; i++)
    {
        char row = data[i];
        fb_putpixel(fbnr, x + 0, y + i, row >> 0 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 1, y + i, row >> 1 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 2, y + i, row >> 2 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 3, y + i, row >> 3 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 4, y + i, row >> 4 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 5, y + i, row >> 5 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 6, y + i, row >> 6 & 1 ? color : FB_BLACK_PIXEL);
        fb_putpixel(fbnr, x + 7, y + i, row >> 7 & 1 ? color : FB_BLACK_PIXEL);
    }
}

void fb_putstr(uint64_t fbnr, uint32_t x, uint32_t y, const char* str, uint32_t color)
{
    char* ptr = str;
    int i = 0;
    while (*ptr)
    {
        fb_putchar(fbnr, x + i * 8, y * 8, *ptr, color);
        ptr++, i++;
    }
}
