#ifndef __C19K_KERNEL_H__
#define __C19K_KERNEL_H__

#define C19K_VERSION "1.0"

void kernel_halt_forever(void);
void kernel_panic_void(void);
void kernel_panic(const char* reason);

#endif
