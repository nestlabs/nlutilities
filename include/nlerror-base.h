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
 *      This file defines data and interfaces for manipulating error
 *      and status codes.
 *
 */

#ifndef NLUTILITIES_NLERROR_BASE_H
#define NLUTILITIES_NLERROR_BASE_H

#include <stdint.h>

#include "nlcore-internal.h"

typedef int32_t nlError;

#define nlErrorNegate(code)		(-(code))

/*
 * Error code (least significant) field constants and macros
 */
#define nlErrorCodeBits                 16
#define nlErrorCodeMask                 _nlCoreMask(nlErrorCodeBits)
#define nlErrorCodeShift                0
#define nlErrorCodeEncode(c)            _nlCoreFieldEncode(c, nlErrorCodeShift, nlErrorCodeMask)
#define nlErrorCodeDecode(e)            _nlCoreFieldDecode(nlErrorNegate(e), nlErrorCodeShift, nlErrorCodeMask)
#define nlErrorCodeMin                  0
#define nlErrorCodeMax                  nlErrorCodeMask

/*
 * Error sub-component field constants and macros
 */
#define nlErrorSubComponentBits         12
#define nlErrorSubComponentMask         _nlCoreMask(nlErrorSubComponentBits)
#define nlErrorSubComponentShift        nlErrorCodeBits
#define nlErrorSubComponentEncode(s)    _nlCoreFieldEncode(s, nlErrorSubComponentShift, nlErrorSubComponentMask)
#define nlErrorSubComponentDecode(e)    _nlCoreFieldDecode(nlErrorNegate(e), nlErrorSubComponentShift, nlErrorSubComponentMask)
#define nlErrorSubComponentMin          0
#define nlErrorSubComponentMax          nlErrorSubComponentMask

/*
 * Error component (most significant) field constants and macros
 */
#define nlErrorComponentBits            3
#define nlErrorComponentMask            _nlCoreMask(nlErrorComponentBits)
#define nlErrorComponentShift           (nlErrorCodeBits + nlErrorSubComponentBits)
#define nlErrorComponentEncode(c)       _nlCoreFieldEncode(c, nlErrorComponentShift, nlErrorComponentMask)
#define nlErrorComponentDecode(e)       _nlCoreFieldDecode(nlErrorNegate(e), nlErrorComponentShift, nlErrorComponentMask)
#define nlErrorComponentMin             0
#define nlErrorComponentMax             nlErrorComponentMask

#define nlErrorCast(v)                  _nlCoreStaticCast(nlError, v)

/*
 * By convention, error codes as returned by functions are always < 0.
 */
#define nlERROR(code)                   nlErrorCast(nlErrorNegate(code))

/*
 * Compose an error from its encoded component, subcomponent and code fields.
 */
#define nlErrorCompose(comp, sub, code) nlERROR((comp) | (sub) | (code))

/*
 * Encode an error from its component, subcomponent and code fields.
 */
#define nlErrorEncode(comp, sub, code)  nlErrorCompose(nlErrorComponentEncode(comp),   \
                                                       nlErrorSubComponentEncode(sub), \
                                                       nlErrorCodeEncode(code))

/*
 * Macro to introspect whether an error is of a particular component
 * and subcomponent.
 */
#define nlErrorIs(comp, sub, error)     ((nlErrorComponentEncode(comp) | nlErrorSubComponentEncode(sub)) == (nlErrorNegate(error) & ~(nlErrorCodeMask)))

/*
 * By convention, success is always identically 0.
 */
#define nlSUCCESS                       nlERROR(0)

#endif /* NLUTILITIES_NLERROR_BASE_H */
