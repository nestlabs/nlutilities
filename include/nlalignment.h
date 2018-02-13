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
 *      This file defines defines macros for handling aligned static
 *      storage declaration.
 *
 */

#ifndef NLUTILITIES_NLALIGNMENT_H
#define NLUTILITIES_NLALIGNMENT_H

#include <stdint.h>

#define nlDEFINE_ALIGNED_VAR(varName, bytes, alignment_type) \
    alignment_type varName[(((bytes) + (sizeof(alignment_type) - 1)) / sizeof(alignment_type))]

#endif // NLUTILITIES_NLALIGNMENT_H
