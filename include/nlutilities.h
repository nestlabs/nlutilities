/*
 *
 *    Copyright (c) 2014-2018 Nest Labs, Inc.
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
 *      This file is an umbrella header for Nest Labs Utilities C
 *      interfaces.
 *
 */

#ifndef NLUTILITIES_NLUTILITIES_H
#define NLUTILITIES_NLUTILITIES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <nlbase64.h>
#include <nlcore.h>
#include <nlfixedpoint.h>
#include <nlmacros.h>
#include <nlmemset16.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int nl_hextobin(char c);
extern void nl_strhextobin(uint8_t *bin, const char *hex, size_t len);

/*!
    Write an array of bytes out as a hex string. Caller should ensure that
    the size of dest is large enough to hold the hex string, plus separators,
    plus 1 byte for the null terminator.
    Can optionally pass in a separator character in sep. Leave null
    otherwise.
    @arg dest The destination buffer to put the hex string
    @arg src The source buffer containing the binary data
    @arg srclen The length of the source buffer
    @arg sep The separator character to use between chunks
*/
extern char *nl_bintohexstr(char *dest, const uint8_t *src, size_t len, char sep);
extern bool nl_isxdigitstr(const char *s);
extern int nl_getCharSeparatedBytes(const char* inBuffer, uint8_t* outBytes, size_t inNumValues, char inSeparator, int inBase);
extern void nl_dump_bytes(uintptr_t offs, const uint8_t *bytes, size_t num);
extern void nl_printBytesWithSeparator( const uint8_t* inBytes, size_t inNumValues, char inSeparator);
extern size_t nl_strncpyprettyprint(char *inOutDest, const char *inSource, size_t inBufferCapacity);

#ifdef __cplusplus
}
#endif

#endif // NLUTILITIES_NLUTILITIES_H
