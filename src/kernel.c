#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "limine.h"

#include "kernel.h"
#include "kassert.h"
#include "kstdlib.h"
#include "terminal/kterminal.h"
#include "framebuffer/fb.h"

void kernel_halt_forever(void)
{
    for (;;) __asm__("hlt");
}

// Most likely we are not able to even print a message to user, very rare
void kernel_panic_void(void)
{
    kernel_halt_forever();
}

// Print an error message and bail out
void kernel_panic(const char* reason)
{
    fb_putstr(0, 8, 1, "Kernel Panic!", FB_RED_PIXEL);
    fb_putstr(0, 8, 2, reason, FB_RED_PIXEL);
    kernel_halt_forever();
}

const char* c19kmotd =
    "C19 Kernel "
    "["
#ifdef __clang__
    "LLVM clang " STRINGIZE(__clang_major__) "." STRINGIZE(__clang_minor__) "." STRINGIZE(__clang_patchlevel__) ", "
#else
    "GNU CC " STRINGIZE(__GNUC__) "." STRINGIZE(__GNUC_MINOR__) "." STRINGIZE(__GNUC_PATCHLEVEL__) ", "
#endif
    "STDC " STRINGIZE(__STDC_VERSION__) "], "
    "Build Date " __DATE__ " " __TIME__
    ;

void _start(void)
{
    // Be sure that we have a framebuffer to work on
    ASSERT_VOID(fb_check(0));

    fb_putstr(0, 5, 1, c19kmotd, FB_WHITE_PIXEL);

    struct kernel_terminal term;
    kterm_setup(&term, 0);

    fb_putstr(0, 5, 2, "Terminal set-up, switching modes...", FB_WHITE_PIXEL);

    kernel_halt_forever();
}
