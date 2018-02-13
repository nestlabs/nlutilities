/*
 *
 *    Copyright (c) 2015-2018 Nest Labs, Inc.
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
 *      This file defines interfaces for performing integer to
 *      fixed point numerical conversions.
 *
 */

#include <nlfixedpoint.h>

#include <stdint.h>

int nl_uint16_to_fixed32(uint32_t *result, uint16_t raw_value, uint32_t scale_factor, size_t desired_frac_bits)
{
    return nl_uint32_to_fixed32(result, raw_value, scale_factor, desired_frac_bits);
}

int nl_int16_to_fixed32(int32_t *result, int16_t raw_value, uint32_t scale_factor, size_t desired_frac_bits)
{
    return nl_int32_to_fixed32(result, raw_value, scale_factor, desired_frac_bits);
}

int nl_uint32_to_fixed32(uint32_t *result, uint32_t raw_value, uint32_t scale_factor, size_t desired_frac_bits)
{
    int err;

    // desired_frac_bits should <= 31
    if (desired_frac_bits > 31)
    {
        err = -1;
    }
    else
    {
        uint64_t Qvalue = nlStaticCast(uint64_t, raw_value) * scale_factor;

        Qvalue = Qdown(31, desired_frac_bits, Qvalue);

        // size of m should be sufficient enough to store the integer portion of result
        if (Qvalue > UINT32_MAX)
        {
            err = -1;
        }
        else
        {
            *result = nlStaticCast(uint32_t, Qvalue);
            err = 0;
        }
    }

    return err;
}

int nl_int32_to_fixed32(int32_t *result, int32_t raw_value, uint32_t scale_factor, size_t desired_frac_bits)
{
    uint32_t uint_value;
    uint32_t uint_result;
    int err;

    uint_value = (raw_value < 0) ? ((~raw_value) + 1) : raw_value;

    err = nl_uint32_to_fixed32(&uint_result, uint_value, scale_factor, desired_frac_bits);

    if (err == 0)
    {
        *result = (raw_value < 0) ? nlStaticCast(int32_t, (~uint_result) + 1) : nlStaticCast(int32_t, uint_result);
    }

    return err;
}
