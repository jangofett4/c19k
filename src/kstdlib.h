#ifndef __C19K_KSTDLIB_H__
#define __C19K_KSTDLIB_H__

#include <stdint.h>

#define SWAP(l, r) do { __typeof__(l) ltmp = l; l = r; r = ltmp; } while(0)

void reverse(char* buffer, uint32_t length);

uint32_t strlen(const char* buffer);

void lpad(char* buffer, uint32_t length);
void rpad(char* buffer, uint32_t length);

void u64_to_str(uint64_t data, char* buffer);
void f64_to_str(double data, char* buffer, int precision);

void u64_to_base_string(uint64_t data, uint32_t base, char* buffer);

void kmemcpy(char* from, char* to, uint32_t start, uint32_t size, uint32_t dstart);

#endif
