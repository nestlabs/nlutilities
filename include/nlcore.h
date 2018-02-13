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
 *      This file is an umbrella header for a library of C core data,
 *      interfaces and classes for Nest Labs applications and
 *      libraries.
 *
 */

#ifndef NLUTILITIES_NLCORE_H
#define NLUTILITIES_NLCORE_H

#include <nlalignment.h>
#include <nlcore-internal.h>
#include <nlerror.h>

#define nlMask(bits)               _nlCoreMask(bits)

#define nlFieldEncode(f, s, m)     _nlCoreFieldEncode(f, s, m)
#define nlFieldDecode(v, s, m)     _nlCoreFieldDecode(v, s, m)

#define nlConstCast(t, v)          _nlCoreConstCast(t, v)
#define nlReinterpretCast(t, v)    _nlCoreReinterpretCast(t, v)
#define nlStaticCast(t, v)         _nlCoreStaticCast(t, v)

#endif // NLUTILITIES_NLCORE_H
