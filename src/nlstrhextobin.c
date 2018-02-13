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
 *      This file implements an interface for converting a hexadecimal
 *      encoded bytes stream to a binary encoded stream.
 *
 */

#include <nlutilities.h>

void nl_strhextobin(uint8_t *bin, const char *hex, size_t len)
{
    size_t i;

    for (i = 0; i < len; i++) {
        bin[i] = (nl_hextobin(hex[i * 2 + 0]) << 4 |
                  nl_hextobin(hex[i * 2 + 1]) << 0);
    }
}
