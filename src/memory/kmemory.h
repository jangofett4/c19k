#ifndef __C19K_KMEMORY_H__
#define __C19K_KMEMORY_H__

#include <stdint.h>

class PageAllocator
{
    uint32_t page_tally;

public:
    PageAllocator();
    ~PageAllocator();
};

#endif