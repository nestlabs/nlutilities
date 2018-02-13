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
 *      This file defines a base class which classes may derive from
 *      to enforce C++ noncopyability.
 *
 */

#ifndef NLUTILITIES_NLNONCOPYABLE_HPP
#define NLUTILITIES_NLNONCOPYABLE_HPP

namespace nl
{

namespace _noncopyable
{

class noncopyable
{
protected:
    noncopyable(void) { }
    ~noncopyable(void) { }

private:
    noncopyable(const noncopyable &);
    const noncopyable &operator =(const noncopyable &);
};

}; // namespace _noncopyable

typedef _noncopyable::noncopyable noncopyable;

}; // namespace nl

#endif // NLUTILITIES_NLNONCOPYABLE_HPP
