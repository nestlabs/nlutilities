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
 *      This file implements a utility function for pretty-printing a
 *      string that may contain non-printable characters.
 *
 */

#include <nlutilities.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nlcore.h>

size_t nl_strncpyprettyprint(char *inOutDest, const char *inSource, size_t inBufferCapacity)
{
    size_t written = 0;

    if ((inOutDest == NULL) || (inSource == NULL))
    {
        goto done;
    }

    while (inBufferCapacity > 1)
    {
        inBufferCapacity--;

        char c = *inSource++;
        // null terminator, break
        if (c == 0)
        {
            break;
        }

        if (!isprint(nlStaticCast(int, c)))
        {
            c = '.';
        }

        *inOutDest++ = c;
        written++;
    }

    if (inBufferCapacity != 0)
    {
        *inOutDest = 0;
        written++;
    }

done:
    return written;
}
