#ifndef __LIBRARY_LIBC_STDINT_H__
#define __LIBRARY_LIBC_STDINT_H__

#ifdef __GNUC__

using u8 = __UINT8_TYPE__;
using uint8_t = u8;
using u16 = __UINT16_TYPE__;
using uint16_t = u16;
using u32 = __UINT32_TYPE__;
using uint32_t = u32;
using u64 = __UINT64_TYPE__;
using uint64_t = u64;
static_assert(sizeof(u8) == 1, "u8 must be size of 1");
static_assert(sizeof(u16) == 2, "u8 must be size of 2");
static_assert(sizeof(u32) == 4, "u8 must be size of 4");
static_assert(sizeof(u64) == 8, "u8 must be size of 8");

using i8 = __INT8_TYPE__;
using int8_t = i8;
using i16 = __INT16_TYPE__;
using int16_t = i16;
using i32 = __INT32_TYPE__;
using int32_t = i32;
using i64 = __INT64_TYPE__;
using int64_t = i64;
static_assert(sizeof(i8) == 1, "u8 must be size of 1");
static_assert(sizeof(i16) == 2, "u8 must be size of 2");
static_assert(sizeof(i32) == 4, "u8 must be size of 4");
static_assert(sizeof(i64) == 8, "u8 must be size of 8");

using iptr = __INTPTR_TYPE__;
using uptr = __UINTPTR_TYPE__;
using usize = __SIZE_TYPE__;
using size_t = usize;
#if __SIZEOF_LONG__ == 4
static_assert(sizeof(iptr) == 4, "iptr must be size of 4");
static_assert(sizeof(uptr) == 4, "uptr must be size of 4");
static_assert(sizeof(usize) == 4, "usize must be size of 4");
static_assert(sizeof(size_t) == 4, "size_t must be size of 4");
#elif __SIZEOF_LONG__ == 8
static_assert(sizeof(iptr) == 8, "iptr must be size of 8");
static_assert(sizeof(uptr) == 8, "uptr must be size of 8");
static_assert(sizeof(usize) == 8, "usize must be size of 8");
static_assert(sizeof(size_t) == 8, "size_t must be size of 8");
#else
#error "unknown __SIZEOF_LONG__, define your __SIZEOF_LONG__"
#endif

using intmax_t = __INTMAX_TYPE__;
using uintptr_t = uptr;
using ptrdiff_t = __PTRDIFF_TYPE__;
#if __SIZEOF_LONG__ == 4
static_assert(sizeof(intmax_t) == 8, "intmax_t must be size of 8");
static_assert(sizeof(uintptr_t) == 4, "uintptr_t must be size of 4");
static_assert(sizeof(ptrdiff_t) == 4, "ptrdiff_t must be size of 4");
#elif __SIZEOF_LONG__ == 8
static_assert(sizeof(intmax_t) == 8, "intmax_t must be size of 8");
static_assert(sizeof(uintptr_t) == 8, "uintptr_t must be size of 8");
static_assert(sizeof(ptrdiff_t) == 8, "ptrdiff_t must be size of 8");
#else
#error "unknown __SIZEOF_LONG__, define your __SIZEOF_LONG__"
#endif

#else
#error "currently only gcc(g++) is supported now, define your implemntation here"
#endif

#endif// __LIBRARY_LIBC_STDINT_H__
