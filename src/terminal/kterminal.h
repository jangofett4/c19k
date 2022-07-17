#ifndef __C19K_KTERMINAL_H__
#define __C19K_KTERMINAL_H__

#include <stdint.h>

struct kernel_terminal
{
    uint32_t rows, columns;
    uint32_t x, y;
    uint64_t width, height;
    uint32_t back_color;
    uint32_t text_color;

    uint32_t padding_top;       // Not yet used
    uint32_t padding_bottom;    // Not yet used

    uint64_t _fbnr;
    uint32_t* _buffer;
    uint64_t _bufsize;
};

void kterm_setup(struct kernel_terminal* terminal, uint64_t fbnr);
void kterm_setcolor(struct kernel_terminal* terminal, uint32_t back, uint32_t front);
void kterm_clear(struct kernel_terminal* terminal);
void kterm_clearcolor(struct kernel_terminal* terminal, uint32_t color);
void kterm_putc(struct kernel_terminal* terminal, char chr);
void kterm_write(struct kernel_terminal* terminal, const char* str);
void kterm_write_u64(struct kernel_terminal* terminal, uint64_t data);
void kterm_write_f64(struct kernel_terminal* terminal, float data);
void kterm_write_hex(struct kernel_terminal* terminal, uint64_t data);
void kterm_writef(struct kernel_terminal* terminal, const char* format, ...);
void kterm_newline(struct kernel_terminal* terminal);
void kterm_scroll(struct kernel_terminal* terminal, uint32_t lines);

#endif
