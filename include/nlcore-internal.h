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
 *      This file defines macros and interfaces internal to the Nest
 *      Labs core library implementation.
 *
 */

#ifndef NLUTILITIES_NLCORE_INTERNAL_H
#define NLUTILITIES_NLCORE_INTERNAL_H

#include <stdint.h>

#define _nlCoreMask(bits)               ((1 << (bits)) - 1)

#define _nlCoreFieldEncode(f, s, m)     (((f) & (m)) << (s))
#define _nlCoreFieldDecode(v, s, m)     (((v) >> (s)) & (m))

#ifdef __cplusplus
#define _nlCoreConstCast(t, v)          const_cast<t>(v)
#define _nlCoreReinterpretCast(t, v)    reinterpret_cast<t>(v)
#define _nlCoreStaticCast(t, v)         static_cast<t>(v)
#else
#define _nlCoreConstCast(t, v)          ((t)(v))
#define _nlCoreReinterpretCast(t, v)    ((t)(v))
#define _nlCoreStaticCast(t, v)         ((t)(v))
#endif /* __cplusplus */

#endif /* NLUTILITIES_NLCORE_INTERNAL_H */
