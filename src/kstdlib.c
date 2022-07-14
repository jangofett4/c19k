#include "kstdlib.h"

void reverse(char* buffer, uint32_t length)
{
    for (int i = 0; i < length / 2; i++)
        SWAP(buffer[i], buffer[length - i - 1]);
}

void u64_dec_str(uint64_t data, char* buffer)
{
    int i = 0;
    while (data)
    {
        uint8_t rem = data % 10;
        data = data / 10;
        buffer[i++] = rem + 48;
    }
    reverse(buffer, i);
}
