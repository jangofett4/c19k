#include "fb.h"

#include "../kernel.h"

/*
#include "font8x8_basic.h"
*/

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

bool fb_check(uint64_t fbnr)
{
    return framebuffer_request.response && framebuffer_request.response->framebuffer_count > fbnr;
}

uint64_t fb_width(uint64_t fbnr) { return framebuffer_request.response->framebuffers[fbnr]->width; }
uint64_t fb_height(uint64_t fbnr) { return framebuffer_request.response->framebuffers[fbnr]->height; }

struct limine_framebuffer* fb_get(uint64_t fbnr)
{
    return framebuffer_request.response->framebuffers[fbnr];
}

uint32_t* fb_get_buffer(uint64_t fbnr)
{
    return (uint32_t*)framebuffer_request.response->framebuffers[fbnr]->address;
}

void fb_putpixel(uint64_t fbnr, uint32_t x, uint32_t y, uint32_t color)
{
    uint64_t width = framebuffer_request.response->framebuffers[fbnr]->width;
    ((uint32_t*)framebuffer_request.response->framebuffers[fbnr]->address)[width * y + x] = color;
}
