/*
 *
 *    Copyright (c) 2016-2018 Nest Labs, Inc.
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
 *      This file implements an interface for filling memory, 16-bits at
 *      a time, with a constant 16-bit pattern.
 *
 */

#include <nlmemset16.h>

#include <stdint.h>
#include <string.h>

#include <nlcore.h>

#define BLOCKSIZE_64_IN_HALF_WORDS ((sizeof(uint64_t)) / (sizeof(uint16_t)))
#define UNALIGNED_64(x) (nlStaticCast(uintptr_t, (x)) & ((sizeof(uint64_t)) - 1))

/* nl_memset16
 * dst: ptr to memory to set
 * val: 16 bit value to set
 * num_half_words: number of 16 bit half words to set to val
 */
void *nl_memset16(void *dst, int val, size_t num_half_words)
{
    uint64_t val_4;
    uint64_t *aligned_64_dest;
    uint16_t *unaligned_dest = nlStaticCast(uint16_t *, dst);

    val &= 0xFFFF;

    while (UNALIGNED_64(unaligned_dest))
    {
        if (num_half_words--)
        {
            *unaligned_dest++ = val;
        }
        else
        {
            return dst;
        }
    }

    if (num_half_words >= BLOCKSIZE_64_IN_HALF_WORDS)
    {
        aligned_64_dest = nlStaticCast(uint64_t *, unaligned_dest);

        val_4 = val;
        val_4 = (val_4 << 16) | val_4;
        val_4 = (val_4 << 32) | val_4;

        while (num_half_words >= BLOCKSIZE_64_IN_HALF_WORDS * 4)
        {
            *aligned_64_dest++ = val_4;
            *aligned_64_dest++ = val_4;
            *aligned_64_dest++ = val_4;
            *aligned_64_dest++ = val_4;
            num_half_words -= BLOCKSIZE_64_IN_HALF_WORDS * 4;
        }

        while (num_half_words >= BLOCKSIZE_64_IN_HALF_WORDS)
        {
            *aligned_64_dest++ = val_4;
            num_half_words -= BLOCKSIZE_64_IN_HALF_WORDS;
        }

        unaligned_dest = nlStaticCast(uint16_t *, aligned_64_dest);
    }

    while (num_half_words--)
    {
        *unaligned_dest++ = val;
    }

    return dst;
}
