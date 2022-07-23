#include "paging.h"

PageManager::PageManager(uint64_t* pml4base)
{
    this->pml4base = pml4base;
}

PageManager::~PageManager()
{

}

void PageManager::PagingInfo(KernelTerminal* terminal)
{

}