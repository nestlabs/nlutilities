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
 *      This file defines interfaces for variants of the stdlib abs() function.
 */

#ifndef NLUTILITIES_NLABS_VARIANTS_H
#define NLUTILITIES_NLABS_VARIANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Same as abs(), but returns an unsigned int rather than an int,
 * so abs_uint(INT_MIN) can return the absolute value of INT_MIN.
 */
extern unsigned int abs_uint(int n);

/* Same as abs(), except abs_approx(INT_MIN) returns INT_MAX,
 * which is only off by one rather than off by more than 2 * INT_MAX.
 */
 extern int abs_approx(int n);

/* Returns the negative absolute value of the input. Correct for all inputs:
 * nabs(INT_MIN) returns INT_MIN, and nabs(INT_MAX) returns -INT_MAX.
 */
int nabs(int n);

#ifdef __cplusplus
}
#endif

#endif // NLUTILITIES_NLABS_VARIANTS_H
