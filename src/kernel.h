#ifndef __C19K_KERNEL_H__
#define __C19K_KERNEL_H__

#include "terminal/kterminal.h"
#include "limine.h"

#define C19K_VERSION "1.0"

void compiler_cpu_feature_list(int* list);

void kernel_setup_panic(struct kernel_terminal* terminal);
void kernel_halt_forever(void);
void kernel_panic_void(void);
void kernel_panic(const char* reason);
const char* limine_memmap_type_string(uint32_t type);
uint64_t usable_memory_on_boot(struct limine_memmap_entry** entries, uint64_t count);

#endif
