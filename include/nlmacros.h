/*
 *
 *    Copyright (c) 2012-2018 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file implements C preprocessor macro functions for
 *      performing a variety of extrema algorithms and other
 *      mathematical operations.
 *
 */

#ifndef NLUTILITIES_NLMACROS_H
#define NLUTILITIES_NLMACROS_H

// INCLUDE
#include <stddef.h> // for offsetof
#include <limits.h> // for CHAR_BIT

#include <nlcore.h>

// MACROS

// The #ifndefs in this file are for third-party software that defines its
// own identically-named macros, and for our own software that hasn't yet
// been modified to use this shared set of macros.  Eventually, our
// software won't need the #ifndefs.

// Deprecated macros, included for compatibility with legacy code.
#ifndef COMPILE_TIME_ASSERT
#define COMPILE_TIME_ASSERT _NLMACROS_ASSERT
#endif
#ifndef ROUNDUP
#define ROUNDUP(a, b)                           ROUNDUP_U(a, b)
#endif
#define MS_PER_S                                MS_PER_SEC
#define MILLISECONDS_PER_SECOND                 MS_PER_SEC

// MIN and MAX, as usually written, are the canonical examples of macros that
// fail when passed expressions with side-effects (e.g., "MAX(x++, y++)").  Our
// LOG2, CTZ, IS_POW2, and ROUNDDOWN/ROUNDUP macros have similar issues with
// side effects.
//
// For C programs, we solve this problem by using safer macros that require the
// statement-expression and typeof extensions, and the __COUNTER__ predefined
// macro, provided by GCC and Clang.  For C++ programs, there's a subtle case
// where those macros will fail (see GCC's statement-expression documentation
// for details), so we use the usual macros; they still have a side-effects
// problem, but at least that one is well-known and therefore easier to debug
// than the obscure problem with statement expressions in C++.

// We always set BUILD_FEATURE_USE_UNSAFE_MACROS to 1 for C++ programs.  If the
// unsafe versions of the macros are desired for C programs as well, set
// BUILD_FEATURE_USE_UNSAFE_MACROS to 1 on the command line or in the makefile.

#ifdef __cplusplus
#define BUILD_FEATURE_USE_UNSAFE_MACROS 1
#endif

#ifdef BUILD_FEATURE_USE_UNSAFE_MACROS

// Unsafe macros.

#ifndef MIN
#define MIN(a, b)                               ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b)                               ((a) > (b) ? (a) : (b))
#endif

#ifndef LOG2
#define LOG2(x)                                 ((x) != 0 ? 31 - __builtin_clz(x) : -1)
#endif
#ifndef CTZ
#define CTZ(x)                                  ((x) != 0 ? __builtin_ctz(x) : -1)
#endif
#ifndef IS_POW2
#define IS_POW2(x)                              (((x) & ((x) - 1)) == 0)
#endif

// ROUNDDOWN and ROUNDUP_U/ROUNDUP_S actually perform "round toward 0" and
// "round away from 0", respectively (and they only perform it for integral
// types).  ROUNDUP_S works with signed parameters; ROUNDUP_U is just ROUNDUP_S
// simplified for the usual case in which both parameters are unsigned.
#ifndef ROUNDDOWN
#define ROUNDDOWN(a, b)                         ((a) / (b) * (b))
#endif
#define ROUNDUP_S(a, b)                         ROUNDDOWN((a) + ((((a) < 0) == ((b) < 0)) ? (b) : -(b)) + (((a) < 0) ? 1 : -1), b)
#define ROUNDUP_U(a, b)                         ROUNDDOWN((a) + (b) - 1, b)

#else // #ifdef BUILD_FEATURE_USE_UNSAFE_MACROS

// Safer macros.

// MIN and MAX include static asserts that trigger if their two arguments
// differ in signedness.  This prevents, for example, MAX(-1,1U) = -1.
//
// The test for each argument is "(__typeof__(X))(-1) <= 0"; casting the "-1"
// to the type of X forces it to become unsigned if X is unsigned, so the test
// simplifies to either "-1 <= 0" (true) or "-1U <= 0" (false, because "-1U"
// is a large all-ones positive number).  If the two macro arguments have
// different signedness, the two test results will be different and we'll
// trigger the assert.
//
// Note that the comparison is "<= 0" rather than "< 0" in order to avoid
// "comparison is always false" warnings when X is unsigned.
//
// Note also that we're testing the signedness AS WRITTEN (that is, before
// integer promotion).  This means that we will not assert on a comparison
// between uint16_t and uint32_t, and we WILL assert on a comparison between
// uint16_t and int32_t, even though in both cases the compiler will internally
// promote the unsigned uint16_t to a SIGNED int_32_t for the comparison.
#ifndef MIN
#define MIN(a, b)                               MIN_INNER(a, b, __COUNTER__)
#define MIN_INNER(a, b, C)                      ({ __typeof__(a) _CC(_a, C) = (a); __typeof__(b) _CC(_b, C) = (b); _NLMACROS_ASSERT(((__typeof__(a))(-1) <= 0) == ((__typeof__(b))(-1) <= 0)); (_CC(_a, C) < _CC(_b, C)) ? _CC(_a, C) : _CC(_b, C); })
#endif

#ifndef MAX
#define MAX(a, b)                               MAX_INNER(a, b, __COUNTER__)
#define MAX_INNER(a, b, C)                      ({ __typeof__(a) _CC(_a, C) = (a); __typeof__(b) _CC(_b, C) = (b); _NLMACROS_ASSERT(((__typeof__(a))(-1) <= 0) == ((__typeof__(b))(-1) <= 0)); (_CC(_a, C) > _CC(_b, C)) ? _CC(_a, C) : _CC(_b, C); })
#endif

#ifndef LOG2
#define LOG2(x)                                 LOG2_INNER(x, __COUNTER__)
#define LOG2_INNER(x, C)                        ({ __typeof__(x) _CC(_x, C) = (x); (_CC(_x, C) != 0) ? 31 - __builtin_clz(_CC(_x, C)) : -1; })
#endif
#ifndef CTZ
#define CTZ(x)                                  CTZ_INNER(x, __COUNTER__)
#define CTZ_INNER(x, C)                         ({ __typeof__(x) _CC(_x, C) = (x); (_CC(_x, C) != 0) ? __builtin_ctz(_CC(_x, C)) : -1; })
#endif
#ifndef IS_POW2
#define IS_POW2(x)                              IS_POW2_INNER(x, __COUNTER__)
#define IS_POW2_INNER(x, C)                     ({ __typeof__(x) _CC(_x, C) = (x); ((_CC(_x, C) & (_CC(_x, C) - 1)) == 0); })
#endif

// ROUNDDOWN and ROUNDUP_U/ROUNDUP_S actually perform "round toward 0" and
// "round away from 0", respectively (and they only perform it for integral
// types).  ROUNDUP_S works with signed or unsigned parameters; ROUNDUP_U is
// just ROUNDUP_S simplified for the usual case in which both parameters are
// unsigned, and it contains a static assert (with a test similar to the one
// described above for MIN and MAX) that triggers if either argument is signed.
#ifndef ROUNDDOWN
#define ROUNDDOWN(a, b)                         ROUNDDOWN_INNER(a, b, __COUNTER__)
#define ROUNDDOWN_INNER(a, b, C)                ({ __typeof__(a) _CC(_a, C) = (a); __typeof__(b) _CC(_b, C) = (b); _CC(_a, C) / _CC(_b, C) * _CC(_b, C); })
#endif
#define ROUNDUP_S(a, b)                         ROUNDUP_S_INNER(a, b, __COUNTER__)
#define ROUNDUP_S_INNER(a, b, C)                ({ __typeof__(a) _CC(_a, C) = (a); __typeof__(b) _CC(_b, C) = (b); ROUNDDOWN(_CC(_a, C) + ((_CC(_a, C) < 0 == _CC(_b, C) < 0) ? _CC(_b, C) : -_CC(_b, C)) + ((_CC(_a, C) < 0) ? 1 : -1), _CC(_b, C)); })
#define ROUNDUP_U(a, b)                         ROUNDUP_U_INNER(a, b, __COUNTER__)
#define ROUNDUP_U_INNER(a, b, C)                ({ __typeof__(a) _CC(_a, C) = (a); __typeof__(b) _CC(_b, C) = (b); _NLMACROS_ASSERT(((__typeof__(a))(-1) > 0) && ((__typeof__(b))(-1) > 0)); ROUNDDOWN(_CC(_a, C) + _CC(_b, C) - 1, _CC(_b, C)); })

#endif // #ifdef BUILD_FEATURE_USE_UNSAFE_MACROS

// Each parameter evaluated once
#ifndef BITMASK
#define BITMASK(b, s)                           ((~(~0 << (b))) << (s))
#endif
#ifndef NL_BIT
#define NL_BIT(s)                               BITMASK(1, s)
#endif

// Parameters not evaluated (no side-effects)
#ifndef BITS
#define BITS(a)                                 (sizeof(a) * CHAR_BIT)
#endif
#ifndef TYPE_MIN
#define TYPE_MIN(t)                             ((__typeof__(t)) ((__typeof__(t)) -1 > 0 ? 0 : (((__typeof__(t))1) << (BITS(t) - 1))))
#endif
#ifndef TYPE_MAX
#define TYPE_MAX(t)                             ((__typeof__(t)) (~TYPE_MIN(t)))
#endif
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)                           (sizeof(a) / sizeof(*(a)))
#endif
#ifndef ARRAY_LAST
#define ARRAY_LAST(a)                           (&((a)[ARRAY_SIZE(a) - 1]))
#endif

// In the extraordinarily unlikely event that this code is passed to a pre-C89
// compiler (or one without a compliant stddef.h that includes "offsetof"),
// we'll use our own OFFSETOF macro.  Otherwise, we'll use the one provided by
// the compiler, which is at least no worse than ours and might be better.
#ifndef OFFSETOF
#ifndef offsetof
#define OFFSETOF(type, member)                  (nlStaticCast(size_t, &(nlStaticCast(type *, 0)->member)))
#else
#define OFFSETOF(type, member)                  offsetof(type, member)
#endif
#endif

// The "(1 ? (pointer) : &((type *)0)->member)" is functionally equivalent to
// "(pointer)", but it provides type safety by ensuring that "pointer" points
// to a type compatible with "member" (because the conditional operator requires
// pointer operands to be of compatible type).
#ifndef CONTAINEROF
#define CONTAINEROF(pointer, type, member)      (nlStaticCast(type *,             \
    (nlStaticCast(char *, (1 ? (pointer) : &(nlStaticCast(type *, 0)->member))) - \
     OFFSETOF(type, member))))
#endif

#ifndef ALIGN_POINTER
#define ALIGN_POINTER(pointer, size)            (nlStaticCast(uint8_t *, nlStaticCast(uintptr_t, (pointer) + ((size) - 1)) & (~((size) - 1))))
#endif

// Bitfield macros
#ifndef M
#define M(s)                                    (((1U << B_##s) - 1) << S_##s)
#endif
#ifndef G
#define G(s, x)                                 (((x) & M_##s) >> S_##s)
#endif
#ifndef V
#define V(s, x)                                 (((x) << S_##s) & M_##s)
#endif

// Compile-time helpers
#ifndef NL_UNUSED
#define NL_UNUSED(varname)                      ((void) (varname))
#endif
#ifndef CONCAT
#define CONCAT(a, b)                            a##b
#endif

// Static assert macro for internal use in this header file only.  This macro
// definition is intended to duplicate the _nlSTATIC_ASSERT macro definition
// in nlassert-internal.h, so if this definition is modified, that one should
// be modified to match.
#if defined(__cplusplus) && (__cplusplus >= 201103L)
# define _NLMACROS_ASSERT(aCondition) static_assert(aCondition, #aCondition)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define _NLMACROS_ASSERT(aCondition) _Static_assert(aCondition, #aCondition)
#else
# ifdef __COUNTER__
#   define _NLMACROS_ASSERT(aCondition) typedef char _CC(STATIC_ASSERT_t_, __COUNTER__)[(aCondition) ? 1 : -1] __attribute__ ((unused))
# else
#   define _NLMACROS_ASSERT(aCondition) typedef char _CC(STATIC_ASSERT_t_, __LINE__)[(aCondition) ? 1 : -1] __attribute__ ((unused))
# endif
#endif /* defined(__cplusplus) && (__cplusplus >= 201103L) */

// Concatenation macro for internal use in this header file only (in case code
// that includes this file defines "CONCAT" differently than we did above).
// Do not use "CONCAT" within this header file; use "_CC" instead.
#define _CC(a, b)                               __CC(a,b)
#define __CC(a, b)                              a##b

//Constants
#ifndef US_PER_MS
#define US_PER_MS                               (1000)
#endif
#ifndef MS_PER_SEC
#define MS_PER_SEC                              (1000)
#endif
#ifndef MS_PER_MIN
#define MS_PER_MIN                              (1000 * 60)
#endif
#ifndef MS_PER_HR
#define MS_PER_HR                               (1000 * 60 * 60)
#endif

#endif // NLUTILITIES_NLMACROS_H
