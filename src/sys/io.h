#ifndef __C19K_IO_H__
#define __C19K_IO_H__

#include <stdint.h>

static void outb(uint16_t port, uint8_t data);
static uint8_t inb(uint16_t port);

#endif