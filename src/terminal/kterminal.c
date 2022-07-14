#include "framebuffer/fb.h"
#include "kterminal.h"

void kterm_setup(struct kernel_terminal* terminal, uint64_t fbnr)
{
    terminal->rows = fb_height(fbnr / 8);
    terminal->columns = fb_width(fbnr / 8);
    terminal->x = 0;
    terminal->y = 0;
}

void kterm_write(struct kernel_terminal* terminal, const char* str)
{

}

void kterm_write_decimal(struct kernel_terminal* terminal, uint64_t data)
{

}

void kterm_write_hex(struct kernel_terminal* terminal, uint64_t data)
{

}

void kterm_newline(struct kernel_terminal* terminal)
{

}