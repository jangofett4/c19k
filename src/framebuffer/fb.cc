#include "fb.h"

#include "../kernel.h"

/*
#include "font8x8_basic.h"
*/

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

KernelFramebuffer::KernelFramebuffer(uint32_t fbnr)
{
    fbnr = fbnr;
    fbptr = framebuffer_request.response->framebuffers[fbnr];
    rawptr = static_cast<uint32_t*>(fbptr->address);
    width = fbptr->width;
    height = fbptr->height;
}

KernelFramebuffer::~KernelFramebuffer()
{
}

bool KernelFramebuffer::Check(uint64_t fbnr)
{
    return framebuffer_request.response && framebuffer_request.response->framebuffer_count > fbnr;
}

uint64_t KernelFramebuffer::GetWidth() const { return width; }
uint64_t KernelFramebuffer::GetHeight() const { return height; }

uint32_t* KernelFramebuffer::Raw() const { return static_cast<uint32_t*>(fbptr->address); }

void KernelFramebuffer::PutPixel(uint32_t x, uint32_t y, uint32_t color)
{
    rawptr[width * y + x] = color;
}