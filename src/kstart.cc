#include "kernel.h"
#include "kassert.h"
#include "kstdlib.h"

#include "framebuffer/fb.h"
#include "terminal/kterminal.h"
#include "memory/paging.h"

#include "limine.h"

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

const char *c19kmotd =
    "C19 Kernel "
    "["
#ifdef __clang__
    "LLVM clang " STRINGIZE(__clang_major__) "." STRINGIZE(__clang_minor__) "." STRINGIZE(__clang_patchlevel__) ", "
#else
    "GNU CC " STRINGIZE(__GNUC__) "." STRINGIZE(__GNUC_MINOR__) "." STRINGIZE(__GNUC_PATCHLEVEL__) ", "
#endif
#ifdef __cplusplus
    "C++ " STRINGIZE(__cplusplus)
#else
    "STDC " STRINGIZE(__STDC_VERSION__)
#endif
    "], "
    "Build Date " __DATE__ " " __TIME__
    "\n";

extern "C" void _start(void)
{
    // Be sure that we have a framebuffer to work on
    ASSERT_VOID(KernelFramebuffer::Check(0));

    KernelFramebuffer framebuffer(0);   // Open first framebuffer
    KernelTerminal terminal(0);         // Open first terminal

    struct kernel_terminal term;
    kterm_setup(&term, &framebuffer);
    kernel_setup_panic(&term);


    kterm_writef(&term, c19kmotd);
    kterm_writef(&term, "Terminal set-up: %i x %i (%i rows, %i columns)\n", term.width, term.height, term.rows, term.columns);

    int cpu_features[7];
    compiler_cpu_feature_list(cpu_features);
    kterm_writef(&term,
        "Enabled CPU features:\n"
        " SSE    : %b\n"
        " SSE2   : %b\n"
        " SSE3   : %b\n"
        " SSE4.1 : %b\n"
        " SSE4.2 : %b\n"
        " AVX    : %b\n"
        " AVX2   : %b\n",
    cpu_features[0], cpu_features[1], cpu_features[2], cpu_features[3], cpu_features[4], cpu_features[5], cpu_features[6]);

    ASSERT(memmap_request.response);

    kterm_writef(&term, "Bootloader provided memory map:\n");
    for (uint64_t i = 0; i < memmap_request.response->entry_count; i++)
    {
        struct limine_memmap_entry* entry = memmap_request.response->entries[i];
        kterm_writef(&term, " $g%x$w -> $g%x$w ($g%s$w)\n", entry->base, entry->base + entry->length, limine_memmap_type_string(entry->type));
    }

    uint64_t usable = usable_memory_on_boot(memmap_request.response->entries, memmap_request.response->entry_count);
    kterm_writef(&term, "Usable memory: %i Mib\n", usable / 1024 / 1024);

    uint64_t cr3data;
    __asm__ volatile("movq %%cr3, %[Var]" : [Var] "=r" (cr3data));
    uint64_t* cr3 = reinterpret_cast<uint64_t*>(cr3data);
    kterm_writef(&term, "CR3: *%x, (%x)\n", (uint64_t*)cr3, cr3data);

    // cr3 is currently pointing at the start of PML4
    for (uint64_t i = 0; i < 512; i++)
    {
        uint64_t entry = cr3[i];
        if (entry & 1)
            kterm_writef(&term, "PML4E %i = PRESENT\n");
        else
        {
            kterm_writef(&term, "PML4E ENDS AT %i\n", i);
            break;
        }
    }

    // page_directory_t page_directory;
    // kmemcpy((char*)cr3, (char*)&page_directory, 0, sizeof(page_directory_t), 0);

    kernel_halt_forever();
}
