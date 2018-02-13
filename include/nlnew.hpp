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
 *      This file defines inline for placement memory allocation and
 *      deallocation via the new and delete operators.
 *
 */

#ifndef NLUTILITIES_NLNEW_HPP
#define NLUTILITIES_NLNEW_HPP

#include <stddef.h>

inline void * operator new     (size_t, void * p) throw() { return p; }
inline void * operator new[]   (size_t, void * p) throw() { return p; }

inline void   operator delete  (void *, void *)   throw() { }
inline void   operator delete[](void *, void *)   throw() { }

#endif // NLUTILITIES_NLNEW_HPP
