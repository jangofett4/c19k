#ifndef __C19K_KASSERT_H__
#define __C19K_KASSERT_H__

#include "kernel.h"

#define ASSERT_VOID(expr) if (!(expr)) kernel_panic_void();

#define STRINGIZE_DETAIL(expr) #expr
#define STRINGIZE(expr) STRINGIZE_DETAIL(expr)

#define ASSERT(expr) if (!(expr)) kernel_panic("Assertion failed: " #expr " (File: " __FILE__ ", Line: " STRINGIZE(__LINE__) ")")
#define ASSERT_EQ(l, r) if ((l) != (r)) kernel_panic("Equal Assertion failed: " #l " != " #r)
#define ASSERT_NEQ(l, r) if ((l) == (r)) kernel_panic("Not-Equal Assertion failed: " #l " == " #r)

#endif
