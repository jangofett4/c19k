#include "kstdlib.h"

void reverse(char *buffer, uint32_t length)
{
    for (uint32_t i = 0; i < length / 2; i++)
        SWAP(buffer[i], buffer[length - i - 1]);
}

uint32_t strlen(const char* buffer)
{
    const char* ptr = buffer;
    uint32_t len = 0;
    while (*ptr)
    {
        ptr++;
        len++;
    }

    return len;
}

void lpad(char* buffer, uint32_t length)
{
    // malloc might be needed
}

void rpad(char* buffer, uint32_t length)
{
    // malloc might be needed
}

void u64_to_str(uint64_t data, char *buffer)
{
    if (data == 0)
    {
        buffer[0] = '0';
        return;
    }

    int i = 0;
    while (data)
    {
        uint8_t rem = data % 10;
        data = data / 10;
        buffer[i++] = rem + 48;
    }
    reverse(buffer, i);
    buffer[i] = '\0';
}

void u64_to_base_string(uint64_t data, uint32_t base, char* buffer)
{
    int i = 12;
    int j = 0;

    do{
        buffer[i] = "0123456789ABCDEF"[data % base];
        i--;
        data = data / base;
    }while(data > 0);

    while(++i < 13){
       buffer[j++] = buffer[i];
    }

    buffer[j] = 0;
}

// Very shitty, unoptimized and dumb double to string algorithm
void f64_to_str(double data, char *buffer, int precision)
{
    int64_t int_part = (int64_t)data;
    double float_part = (double)(data - int_part);
    int i = 0;
    while (int_part)
    {
        uint8_t rem = int_part % 10;
        int_part = int_part / 10;
        buffer[i++] = rem + 48;
    }
    reverse(buffer, i);
    char number_buffer[22];
    kmemcpy(buffer, number_buffer, 0, i, 0); // Copy int part
    number_buffer[i] = '.';
    int int_part_end = i + 1;
    i = 0;
    while (precision > 0)
    {
        uint8_t rem = (uint8_t)(float_part * 10);
        float_part = (double)(float_part - rem);
        buffer[i++] = rem + 48;
        precision--;
    }
    kmemcpy(buffer, number_buffer, 0, i, int_part_end);
    kmemcpy(number_buffer, buffer, 0, int_part_end + i, 0);
    buffer[i + int_part_end] = '\0';
}

void kmemcpy(char *from, char *to, uint32_t start, uint32_t size, uint32_t dstart)
{
    uint32_t end = start + size;
    for (uint32_t i = 0; start < end; start++, i++)
        to[dstart + i] = from[start];
}
