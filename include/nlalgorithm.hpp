/*
 *
 *    Copyright (c) 2013-2018 Nest Labs, Inc.
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
 *      This file implements reusable algorithm templates for extrema
 *      and swap algorithms.
 *
 */

#ifndef NLUTILITIES_NLALGORITHM_HPP
#define NLUTILITIES_NLALGORITHM_HPP

namespace nl
{

template <typename _T>
inline const _T &
min(const _T &a, const _T &b)
{
    if (b < a)
        return b;

    return a;
}

template <typename _T>
inline const _T &
max(const _T &a, const _T &b)
{
    if (a < b)
        return b;

    return a;
}

/*
 *  const T & clamp<>()
 *
 *  Description:
 *    This function template clamps the specified object, if
 *    necessary, to the specified range, inclusive.
 *
 *  Parameter(s):
 *    _T      - The type of the object to be clamped.
 *
 *  Input(s):
 *    inValue - A reference to the object to clamp.
 *    inLower - A reference to the lower bound, inclusive, to clamp the
 *              object to.
 *    inUpper - A reference to the upper bound, inclusive, to clamp the
 *              object to.
 *
 *  Output(s):
 *    N/A
 *
 *  Returns:
 *    The clamped object.
 *
 */
template <typename _T>
inline const _T &
clamp(const _T &inValue, const _T &inLower, const _T &inUpper)
{
    return (max(inLower, min(inValue, inUpper)));
}

template<typename _T>
inline void
swap(_T & _a, _T & _b)
{
    const _T _tmp = _a;
    _a = _b;
    _b = _tmp;
}

template <typename _Iterator1, typename _Iterator2>
void
iter_swap(_Iterator1 _a, _Iterator2 _b)
{
    nl::swap(*_a, *_b);
}

template<typename _Iterator1, typename _Iterator2>
void
iter_swap_range(_Iterator1 _a, _Iterator2 _b)
{
    for (; _a != _b; ++_a) iter_swap(_a, _a + 1);
}

}; // namespace nl

#endif // NLUTILITIES_NLALGORITHM_HPP
