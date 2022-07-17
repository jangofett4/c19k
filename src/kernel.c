#include "kernel.h"

#include "terminal/kterminal.h"
#include "framebuffer/fb.h"

void compiler_cpu_feature_list(int *list)
{
    list[0] =
#ifdef __SSE__
        1;
#else
        0;
#endif

    list[1] =
#ifdef __SSE2__
        1;
#else
        0;
#endif

    list[2] =
#ifdef __SSE3__
        1;
#else
        0;
#endif

    list[3] =
#ifdef __SSE4_1__
        1;
#else
        0;
#endif

    list[4] =
#ifdef __SSE4_2__
        1;
#else
        0;
#endif

    list[5] =
#ifdef __AVX__
        1;
#else
        0;
#endif

    list[6] =
#ifdef __AVX2__
        1;
#else
        0;
#endif
}

struct kernel_terminal* default_terminal;

void kernel_setup_panic(struct kernel_terminal* terminal)
{
    default_terminal = terminal;
}

void kernel_halt_forever(void)
{
    for (;;)
        __asm__("hlt");
}

// Most likely we are not able to even print a message to user, very rare
void kernel_panic_void(void)
{
    kernel_halt_forever();
}

// Print an error message and bail out
void kernel_panic(const char *reason)
{
    if (default_terminal)
    {
        kterm_setcolor(default_terminal, FB_BLACK_PIXEL, FB_RED_PIXEL);
        kterm_writef(default_terminal, "!!! KERNEL PANIC !!!\n");
        kterm_writef(default_terminal, reason);
    }
    kernel_halt_forever();
}
