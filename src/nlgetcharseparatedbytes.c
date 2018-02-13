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
 *      This file implements a simple replacement for scanf to be able
 *      to scan character-separated bytes strings (e.g. MAC48/MAC64/EUI64/
 *      et al addresses).
 *
 */

#include <nlutilities.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int nl_getCharSeparatedBytes(const char* inBuffer,
                          uint8_t* outBytes,
                          size_t inNumValues,
                          char inSeparator,
                          int inBase)
{
    const char* current;
    const char* next = inBuffer;
    size_t i;
    for (i = 0; i < inNumValues; i++)
    {
        current = next;
        unsigned int val = strtoul(current, (char**) &next, inBase);
        if ((val > 255)  // out of bound
           ||((i != (inNumValues-1))   // wrong separator
              && (*next != inSeparator))
           ||((i == (inNumValues-1))   // junk at the end
              && (*next != '\0'))
           ||(next == current))        // junk after separator
        {
            break;
        }

        // after having validated the value
        // copy it to the output buffer
        *outBytes++ = (uint8_t) val;

        // skip over the separator
        next++;
    }
    return i;
}


void nl_printBytesWithSeparator( const uint8_t* inBytes, size_t inNumValues, char inSeparator)
{
    size_t i;
    for (i = 0; i < inNumValues; i++)
    {
        printf("%02x%c", *inBytes++, (i != (inNumValues - 1)) ? inSeparator : '\0');
    }
    printf("\n");
}
