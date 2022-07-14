#ifndef __C19K_KSTDLIB_H__
#define __C19K_KSTDLIB_H__

#include <stdint.h>

#define SWAP(l, r) do { __typeof__(l) ltmp = l; l = r; r = ltmp; } while(0)

void reverse(char* buffer, uint32_t length);

void u64_dec_str(uint64_t data, char* buffer);
void u64_hex_str(uint64_t data, char* buffer);

#endif
