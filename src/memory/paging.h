#ifndef __C19K_PAGING_H__
#define __C19K_PAGING_H__

#include <stdint.h>

#include "terminal/kterminal.h"

class PageManager
{
    uint64_t* pml4base;
public:
    PageManager(uint64_t* pml4base);
    ~PageManager();

    void PagingInfo(KernelTerminal* terminal);
};

#endif