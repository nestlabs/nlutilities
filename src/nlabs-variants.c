/*
 *
 *    Copyright (c) 2018 Nest Labs, Inc.
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
 *      This file implements variants of the stdlib abs() function.
 *
 */

#include <nlabs-variants.h>

#include <limits.h>

// The stdlib abs() function takes a signed int as input and returns a
// signed int output. The output is almost always the absolute value of
// the input. But when the input is INT_MIN, the output is also INT_MIN,
// which is basically as wrong as possible: Literally every other integer
// is closer to the correct answer.
//
// Since this behavior is probably an unexpected and unhandled corner case
// in most code, we provide these alternatives to the stdlib abs() function.

// For callers that can handle an unsigned return value.
//
// This function is the same as abs(), but returns an unsigned int rather than
// a signed int, so abs_uint(INT_MIN) can return the absolute value of INT_MIN.

unsigned int abs_uint(int n)
{
    return (n < 0) ? -n : n;
}

// For callers that require the return value to be signed, as it is for abs().
//
// This function is the same as abs(), except abs_approx(INT_MIN) returns
// INT_MAX, which is only off by one rather than off by more than 2 * INT_MAX.

int abs_approx(int n)
{
    return (n >= 0)       ?       n :
           (n == INT_MIN) ? INT_MAX :
                                 -n;
}

// For callers that can accept a signed return value that is always NEGATIVE.
//
// This function returns the negative absolute value of the input. It is
// correct for all inputs: nabs(INT_MIN) returns INT_MIN, and nabs(INT_MAX)
// returns -INT_MAX.

int nabs(int n)
{
    return (n < 0) ? n : -n;
}
