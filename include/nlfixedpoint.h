/*
 *
 *    Copyright (c) 2013-2018 Nest Labs, Inc.
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
 *      This file implements interfaces for performing integer to
 *      fixed point numerical conversions.
 *
 */

#ifndef NLUTILITIES_NLFIXEDPOINT_H
#define NLUTILITIES_NLFIXEDPOINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include <nlcore.h>

// Q macros where QsN (signed) and QuN (unsigned) have N fractional bits
#define Q(type, p, x) nlStaticCast(type, ((x) * (nlStaticCast(type, 1) << (p))))

// All of the following are 32 bits wide
typedef int32_t  qint_t;
typedef uint32_t quint_t;

// signed
#define Qs1(x)  Q(qint_t,  1, (x))
#define Qs2(x)  Q(qint_t,  2, (x))
#define Qs3(x)  Q(qint_t,  3, (x))
#define Qs4(x)  Q(qint_t,  4, (x))
#define Qs5(x)  Q(qint_t,  5, (x))
#define Qs6(x)  Q(qint_t,  6, (x))
#define Qs7(x)  Q(qint_t,  7, (x))
#define Qs8(x)  Q(qint_t,  8, (x))
#define Qs9(x)  Q(qint_t,  9, (x))
#define Qs10(x) Q(qint_t, 10, (x))
#define Qs11(x) Q(qint_t, 11, (x))
#define Qs12(x) Q(qint_t, 12, (x))
#define Qs13(x) Q(qint_t, 13, (x))
#define Qs14(x) Q(qint_t, 14, (x))
#define Qs15(x) Q(qint_t, 15, (x))
#define Qs16(x) Q(qint_t, 16, (x))
#define Qs17(x) Q(qint_t, 17, (x))
#define Qs18(x) Q(qint_t, 18, (x))
#define Qs19(x) Q(qint_t, 19, (x))
#define Qs20(x) Q(qint_t, 20, (x))
#define Qs21(x) Q(qint_t, 21, (x))
#define Qs22(x) Q(qint_t, 22, (x))
#define Qs23(x) Q(qint_t, 23, (x))
#define Qs24(x) Q(qint_t, 24, (x))
#define Qs25(x) Q(qint_t, 25, (x))
#define Qs26(x) Q(qint_t, 26, (x))
#define Qs27(x) Q(qint_t, 27, (x))
#define Qs28(x) Q(qint_t, 28, (x))
#define Qs29(x) Q(qint_t, 29, (x))
#define Qs30(x) Q(qint_t, 30, (x))
#define Qs31(x) Q(qint_t, 31, (x))

// unsigned
#define Qu1(x)  Q(quint_t,  1, (x))
#define Qu2(x)  Q(quint_t,  2, (x))
#define Qu3(x)  Q(quint_t,  3, (x))
#define Qu4(x)  Q(quint_t,  4, (x))
#define Qu5(x)  Q(quint_t,  5, (x))
#define Qu6(x)  Q(quint_t,  6, (x))
#define Qu7(x)  Q(quint_t,  7, (x))
#define Qu8(x)  Q(quint_t,  8, (x))
#define Qu9(x)  Q(quint_t,  9, (x))
#define Qu10(x) Q(quint_t, 10, (x))
#define Qu11(x) Q(quint_t, 11, (x))
#define Qu12(x) Q(quint_t, 12, (x))
#define Qu13(x) Q(quint_t, 13, (x))
#define Qu14(x) Q(quint_t, 14, (x))
#define Qu15(x) Q(quint_t, 15, (x))
#define Qu16(x) Q(quint_t, 16, (x))
#define Qu17(x) Q(quint_t, 17, (x))
#define Qu18(x) Q(quint_t, 18, (x))
#define Qu19(x) Q(quint_t, 19, (x))
#define Qu20(x) Q(quint_t, 20, (x))
#define Qu21(x) Q(quint_t, 21, (x))
#define Qu22(x) Q(quint_t, 22, (x))
#define Qu23(x) Q(quint_t, 23, (x))
#define Qu24(x) Q(quint_t, 24, (x))
#define Qu25(x) Q(quint_t, 25, (x))
#define Qu26(x) Q(quint_t, 26, (x))
#define Qu27(x) Q(quint_t, 27, (x))
#define Qu28(x) Q(quint_t, 28, (x))
#define Qu29(x) Q(quint_t, 29, (x))
#define Qu30(x) Q(quint_t, 30, (x))
#define Qu31(x) Q(quint_t, 31, (x))

// Convert down
#define Qdown(from, to, x) (((x) + (nlMask((from) - (to)))) >> ((from) - (to)))
#define Qint(from, x)      Qdown((from), 0, (x))

// Convert up
#define Qup(from, to, x)   ((x) << ((to) - (from)))

// Return closest n-bit value to x
#define SATURATE(n, x)                          \
    do {                                        \
        switch ((x) >> (n))                     \
        {                                       \
        case 0:                                 \
            (x) = nlMask(n);                    \
            break;                              \
        case -1:                                \
            (x) = (-1 << (n));                  \
            break;                              \
        }                                       \
    } while (0)

/**
 * @defgroup raw_to_fp Raw value to fixed-point conversion
 * @{
 */
/**
 * @brief   Convert raw unsigned 16-bit to unsigned 32-bit fixed point
 *
 * @param[out] result             pointer to store 32-bit result [unit in Qm.n]
 * @param[in]  raw_value          raw 16-bit value [bits]
 * @param[in]  scale_factor       resolution of a bit in 'raw_value', [unit per bit in Q.31]
 * @param[in]  desired_frac_bits  number of fractional bits, n, in the final result
 *
 * @pre desired_frac_bits <= 31
 * @pre size of m is sufficient to store the integer portion of result
 *
 * @return 0 if successful, -1 otherwise
 */
int nl_uint16_to_fixed32(uint32_t *result, uint16_t raw_value, uint32_t scale_factor, size_t desired_frac_bits);

/**
 * @brief   Convert raw signed 16-bit to signed 32-bit fixed point
 *
 * @param[out] result             pointer to store 32-bit result [unit in Qm.n]
 * @param[in]  raw_value          raw 16-bit value [bits]
 * @param[in]  scale_factor       resolution of a bit in 'raw_value', [unit per bit in Q.31]
 * @param[in]  desired_frac_bits  number of fractional bits, n, in the final result
 *
 * @pre desired_frac_bits <= 31
 * @pre size of m is sufficient to store the integer portion of result
 *
 * @return 0 if successful, -1 otherwise
 */
int nl_int16_to_fixed32(int32_t *result, int16_t raw_value, uint32_t scale_factor, size_t desired_frac_bits);

/**
 * @brief   Convert raw unsigned 32-bit to unsigned 32-bit fixed point
 *
 * @param[out] result             pointer to store 32-bit result [unit in Qm.n]
 * @param[in]  raw_value          raw 32-bit value [bits]
 * @param[in]  scale_factor       resolution of a bit in 'raw_value', [unit per bit in Q.31]
 * @param[in]  desired_frac_bits  number of fractional bits, n, in the final result
 *
 * @pre desired_frac_bits <= 31
 * @pre size of m is sufficient to store the integer portion of result
 *
 * @return 0 if successful, -1 otherwise
 */
int nl_uint32_to_fixed32(uint32_t *result, uint32_t raw_value, uint32_t scale_factor, size_t desired_frac_bits);

/**
 * @brief   Convert raw signed 32-bit to signed 32-bit fixed point
 *
 * @param[out] result             pointer to store 32-bit result [unit in Qm.n]
 * @param[in]  raw_value          raw 32-bit value [bits]
 * @param[in]  scale_factor       resolution of a bit in 'raw_value', [unit per bit in Q.31]
 * @param[in]  desired_frac_bits  number of fractional bits, n, in the final result
 *
 * @pre desired_frac_bits <= 31
 * @pre size of m is sufficient to store the integer portion of result
 *
 * @return 0 if successful, -1 otherwise
 */
int nl_int32_to_fixed32(int32_t *result, int32_t raw_value, uint32_t scale_factor, size_t desired_frac_bits);
/* @} */

#ifdef __cplusplus
}
#endif

#endif /* NLUTILITIES_NLFIXEDPOINT_H */
