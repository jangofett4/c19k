#ifndef __C19K_KTERMINAL_H__
#define __C19K_KTERMINAL_H__

#include <stdint.h>

struct kernel_terminal
{
    uint32_t rows, columns;
    uint32_t x, y;
};

void kterm_setup(struct kernel_terminal* terminal, uint64_t fbnr);
void kterm_write(struct kernel_terminal* terminal, const char* str);
void kterm_write_decimal(struct kernel_terminal* terminal, uint64_t data);
void kterm_write_hex(struct kernel_terminal* terminal, uint64_t data);
void kterm_newline(struct kernel_terminal* terminal);

#endif
