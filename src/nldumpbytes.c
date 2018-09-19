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
 *      This file implements a method to print-print a block of memory
 *      to standard output.
 *
 */

#include <nlutilities.h>

#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void nl_dump_bytes(uintptr_t offs, const uint8_t *bytes, size_t num)
{
    size_t i;
    char lineBuf[17];

    while (num > 0)
    {
        const size_t thisGo = (num >= 16 ? 16 : num);

        printf("%08"PRIXPTR"  ", offs);

        for (i = 0; i < thisGo; i++)
        {
            const uint8_t b = bytes[i];

            lineBuf[i] = (!isprint(b)) ? '.' : b;

            printf("%.02" PRIX8 " ", b);

            if ((i & 3) == 3)
            {
                printf(" ");
            }
            if (i == 7)
            {
                printf(" ");
            }
        }

        lineBuf[i] = 0;
        printf("%s\n", lineBuf);
        num -= thisGo;
        offs += thisGo;
        bytes += thisGo;
    }
}
