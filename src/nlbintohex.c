/*
 *
 *    Copyright (c) 2010-2018 Nest Labs, Inc.
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
 *      This file implements a function that converts the specified
 *      binary-encoded stream to its equivalent hexadecimal
 *      representation, with optional octet delimiters.
 *
 */

#include <nlutilities.h>

static char nibble_to_hex(uint8_t x)
{
    x &= 0xf;

    return (x > 9) ? (x - 10 + 'A') : (x + '0');
}

char *nl_bintohexstr(char *dest, const uint8_t *src, size_t srclen, char sep)
{
    size_t i = 0;
    char *d = dest;

    for (i = 0; i < srclen; i++)
    {
        *d++ = nibble_to_hex(src[i] >> 4);
        *d++ = nibble_to_hex(src[i] & 0xf);
        if (sep && (i & 1) && i < srclen - 1)
        {
            *d++ = sep;
        }
    }

    *d = '\0';

    return dest;
}
