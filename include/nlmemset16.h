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
 *      This file defines an interface for filling memory, 16-bits at
 *      a time, with a constant 16-bit pattern.
 *
 */

#ifndef NLUTILITIES_NLMEMSET16_H
#define NLUTILITIES_NLMEMSET16_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *nl_memset16(void *dst, int val, size_t num_half_words);

#ifdef __cplusplus
}
#endif

#endif //NLUTILITIES_NLMEMSET16_H
