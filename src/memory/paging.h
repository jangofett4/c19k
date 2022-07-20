#ifndef __C19K_PAGING_H__
#define __C19K_PAGING_H__

#include <stdint.h>

struct page_t
{
    uint32_t present    : 1;
    uint32_t rw         : 1;
    uint32_t user       : 1;
    uint32_t accessed   : 1;
    uint32_t dirty      : 1;
    uint32_t unused     : 7;
    uint32_t frame      : 20;
};

struct page_table_t
{
    page_t tables[1024];
};

struct page_directory_t
{
    page_table_t* tables[1024];
};

#endif