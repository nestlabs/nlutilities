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
 *      This file implements a function that determines whether a
 *      NULL-terminated C string conforms to isxdigit.
 *
 */

#include <nlutilities.h>

#include <ctype.h>
#include <stdbool.h>

bool nl_isxdigitstr(const char *s)
{
    int c;
    bool retval = false;

    while (s != NULL && ((c = *s++) != '\0')) {
        retval = isxdigit(c);

        if (!retval)
            break;
    }

    return retval;
}
