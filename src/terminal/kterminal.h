#ifndef __C19K_KTERMINAL_H__
#define __C19K_KTERMINAL_H__

#include <stdint.h>
#include "framebuffer/fb.h"

class KernelTerminal
{
    uint32_t rows, columns;
    uint32_t x, y;
    uint32_t width, height;
    uint32_t back_color, text_color;

    uint32_t padding_top, padding_bottom;

    uint64_t fbnr;
    uint32_t* buffer;
    uint64_t bufsize;

public:
    KernelTerminal(uint64_t fbnr);
    ~KernelTerminal();

    
};

struct kernel_terminal
{
    uint32_t rows, columns;
    uint32_t x, y;
    uint64_t width, height;
    uint32_t back_color;
    uint32_t text_color;

    uint32_t padding_top;       // Not yet used
    uint32_t padding_bottom;    // Not yet used

    KernelFramebuffer* fb;
    uint64_t _bufsize;
};

void kterm_setup(kernel_terminal* terminal, KernelFramebuffer* fb);
void kterm_setcolor(kernel_terminal* terminal, uint32_t back, uint32_t front);
void kterm_clear(kernel_terminal* terminal);
void kterm_clearcolor(kernel_terminal* terminal, uint32_t color);
void kterm_putc(kernel_terminal* terminal, char chr);
void kterm_write(kernel_terminal* terminal, const char* str);
void kterm_write_u64(kernel_terminal* terminal, uint64_t data);
void kterm_write_u64_hex(kernel_terminal* terminal, uint64_t data);
void kterm_write_f64(kernel_terminal* terminal, float data);
void kterm_write_hex(kernel_terminal* terminal, uint64_t data);
void kterm_writef(kernel_terminal* terminal, const char* format, ...);
void kterm_newline(kernel_terminal* terminal);
void kterm_scroll(kernel_terminal* terminal, uint32_t lines);

#endif
