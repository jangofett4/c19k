#include "framebuffer/fb.h"
#include "font8x8_basic.h"
#include "kterminal.h"
#include "kstdlib.h"

#include <stdarg.h>

KernelTerminal::KernelTerminal(uint64_t fbnr)
{

}

KernelTerminal::~KernelTerminal()
{}

void kterm_setup(struct kernel_terminal* terminal, KernelFramebuffer* fb)
{
    uint64_t w = fb->GetWidth();
    uint64_t h = fb->GetHeight();
    terminal->rows = h / 8;
    terminal->columns = w / 8;
    terminal->x = 0;
    terminal->y = 0;
    terminal->width = w;
    terminal->height = h;
    terminal->back_color = FB_BLACK_PIXEL;
    terminal->text_color = FB_WHITE_PIXEL;
    terminal->padding_top = 0;
    terminal->padding_bottom = 0;
    terminal->fb = fb;
    // terminal->_fbnr = fbnr;
    // terminal->_buffer = fb_get_buffer(0);
    terminal->_bufsize = w * h * 4;
}

void kterm_setcolor(struct kernel_terminal* terminal, uint32_t back, uint32_t front)
{
    terminal->back_color = back;
    terminal->text_color = front;
}

void kterm_clear(struct kernel_terminal* terminal)
{
    for (uint32_t x = 0; x < terminal->columns; x++)
        for (uint32_t y = 0; y < terminal->rows; y++)
            terminal->fb->PutPixel(x, y, terminal->back_color);
    terminal->x = 0;
    terminal->y = 0;
}

void kterm_clearcolor(struct kernel_terminal* terminal, uint32_t color)
{
    for (uint32_t x = 0; x < terminal->columns; x++)
        for (uint32_t y = 0; y < terminal->rows; y++)
            terminal->fb->PutPixel(x, y, color);
    terminal->x = 0;
    terminal->y = 0;
}

void kterm_putc(struct kernel_terminal* terminal, char chr)
{
    if (chr == '\n')
    {
        kterm_newline(terminal);
        return;
    }

    uint8_t* data = font8x8_basic[(int)chr];
    uint32_t startx, starty;
    startx = terminal->x * 8;
    starty = terminal->y * 8;
    for (int i = 0; i < 8; i++)
    {
        char row = data[i];
        terminal->fb->PutPixel(startx + 0, starty + i, row >> 0 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 1, starty + i, row >> 1 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 2, starty + i, row >> 2 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 3, starty + i, row >> 3 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 4, starty + i, row >> 4 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 5, starty + i, row >> 5 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 6, starty + i, row >> 6 & 1 ? terminal->text_color : terminal->back_color);
        terminal->fb->PutPixel(startx + 7, starty + i, row >> 7 & 1 ? terminal->text_color : terminal->back_color);
    }
    terminal->x++;
    if (terminal->x >= terminal->columns)
    {
        terminal->x = 0;
        terminal->y++;
        if (terminal->y >= terminal->rows)
        {
            kterm_scroll(terminal, 1);
            terminal->y = terminal->rows - 1;
        }
    }
}

void kterm_write(struct kernel_terminal* terminal, const char* str)
{
    const char* ptr = str;
    while (*ptr)
    {
        kterm_putc(terminal, *ptr);
        ptr++;
    }
}

void kterm_writef(kernel_terminal* terminal, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    const char* ptr = format;
    while (*ptr)
    {
        if (*ptr == '%')
        {
            ptr++;
            char fmt = *ptr;
            if (fmt == '\0') return;
            else if (fmt == '%') kterm_putc(terminal, '%');
            else if (fmt == 'c') kterm_putc(terminal, (char)va_arg(args, uint32_t));
            else if (fmt == 'i') kterm_write_u64(terminal, va_arg(args, uint64_t));
            else if (fmt == 'x') kterm_write_u64_hex(terminal, va_arg(args, uint64_t));
            else if (fmt == 'f') kterm_write_f64(terminal, va_arg(args, double));
            else if (fmt == 's') kterm_write(terminal, va_arg(args, const char*));
            else if (fmt == 'b') kterm_write(terminal, va_arg(args, int32_t) ? "true" : "false");
            ptr++;
            continue;
        }
        else if (*ptr == '$')
        {
            ptr++;
            char fmt = *ptr;
            if (fmt == '\0') return;
            else if (fmt == 'r') kterm_setcolor(terminal, FB_BLACK_PIXEL, FB_RED_PIXEL);
            else if (fmt == 'g') kterm_setcolor(terminal, FB_BLACK_PIXEL, FB_GREEN_PIXEL);
            else if (fmt == 'b') kterm_setcolor(terminal, FB_BLACK_PIXEL, FB_BLUE_PIXEL);
            else if (fmt == 'w') kterm_setcolor(terminal, FB_BLACK_PIXEL, FB_WHITE_PIXEL);
            ptr++;
            continue;
        }

        kterm_putc(terminal, *ptr);

        ptr++;
    }

    va_end(args);
}

void kterm_write_u64(struct kernel_terminal* terminal, uint64_t data)
{
    char buffer[22];
    u64_to_str(data, buffer);
    kterm_write(terminal, buffer);
}

void kterm_write_u64_hex(struct kernel_terminal* terminal, uint64_t data)
{
    char buffer[22];
    u64_to_base_string(data, 16, buffer);
    kterm_write(terminal, buffer);
}

void kterm_write_f64(struct kernel_terminal* terminal, float data)
{
    char buffer[22];
    f64_to_str(data, buffer, 3);
    kterm_write(terminal, buffer);
}

void kterm_write_hex(struct kernel_terminal* terminal, uint64_t data)
{
    char buffer[22];
}

void kterm_newline(struct kernel_terminal* terminal)
{
    terminal->x = 0;
    terminal->y++;
    if (terminal->y >= terminal->rows)
    {
        kterm_scroll(terminal, 1);
        terminal->y--;
    }
}

void kterm_scroll(struct kernel_terminal* terminal, uint32_t lines)
{
    uint32_t* rawbuf = terminal->fb->Raw();
    uint32_t bytes_to_skip = lines * terminal->width * 4 * 8; // 4bpp * 8 height of the font * width of screen * how many lines to scroll
    kmemcpy(
        (char*)rawbuf,
        (char*)rawbuf,
        bytes_to_skip, 
        terminal->_bufsize - bytes_to_skip,
        0
    );
}
