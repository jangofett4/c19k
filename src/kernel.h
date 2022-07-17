#ifndef __C19K_KERNEL_H__
#define __C19K_KERNEL_H__

#include "terminal/kterminal.h"

#define C19K_VERSION "1.0"

void compiler_cpu_feature_list(int* list);

void kernel_setup_panic(struct kernel_terminal* terminal);
void kernel_halt_forever(void);
void kernel_panic_void(void);
void kernel_panic(const char* reason);

#endif
