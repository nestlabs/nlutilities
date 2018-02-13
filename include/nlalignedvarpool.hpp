/*
 *
 *    Copyright (c) 2015-2018 Nest Labs, Inc.
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
 *      This file defines a C++ aligned buffer pool maintaining type
 *      information for the contents.
 *
 */

#ifndef NLUTILITIES_NLALIGNEDVARPOOL_HPP
#define NLUTILITIES_NLALIGNEDVARPOOL_HPP

#include <stdint.h>
#include <stddef.h>

namespace nl
{

/** nl::AlignedVarPool: Alignment-specified variable pool space reservation
  * This is templated on client data type T, count Nct and aligned type Talign.
  * Provides storage of adequate size to use for a class of type T that does not
  * trigger an automatic constructor for type T. placement-new should be called
  * to run a constructor for the class if necessary for type T. Placement-new
  * can directly use the instance name of this type as its pointer because of
  * the casting operators defined on the class. This class also provides some
  * helper functions to call placement-new and potentially call destructors
  * on pool objects. It does not attempt to track which objects are currently
  * constructor or "in-use" itself, that is left to users to track
  * appropriately.
  *
  * Template Parameters:
  *   T: Typename for class requiring storage
  *   Nct: size_t count of copies of type T for which to reserve space. The
  *        default is one object. Various getters and cast operators will
  *        return the first object by default, index dereference operators []
  *        also work via implicit T* cast then usual C-style array offset
  *        pointer conversion.
  *   Talign: Typename for a basic class to use as the alignment for the storage,
  *           this probably should be the largest object type in the class; the
  *           default of a 64-bit integer is the most conservative alignment
  *           expected in the runtime, though that may not be absolutely true.
  *
  *  An instance of this object retains type information and doesn't require
  *  explicit casting for most uses as its referenced type T pointer.
  *  This is essentially a type-retaining version of DEFINE_ALIGNED_VAR in that
  *  you can look at static debug data and know what type of object is actually
  *  stored in various ranges of memory, as well as providing some simple run-
  *  time helpers (Construct/Destroy/Fill) that encapsulate C++ array semantics.
  *  nl::AlignedVarPool<Foo> is not expected to be a stand-in for instances of
  *  Foo except for getting a pointer or reference. It does not attempt to
  *  implement -> operators to forward invocations, for example.
  *
  *  Example Usage:
  *
  *  static nl::AlignedVarPool<Foo> sFooStorage; // declares uint64_t array[]
  *  void initFoo() { new (sFooStorage) Foo(42); } // explicit in-place new
  *  void initFoo2() { sFooStorage.ConstructAll(); } // Helper construction
  *  Foo& getFooInstance() { return sFooStorage; } // invokes operator T&()
  *  void f() { static_cast<Foo*>(sFooStorage)->Invoke(); } // unusual but ok
  *  void g() { getFooInstance().Invoke(); } // better (recommended)
  *  void h() { sFooStorage->Invoke(); } // error: sFooStorage != Foo
  *
  *  Differences from DEFINE_ALIGNED_VAR():
  *
  *  - Helper methods as documented
  *  - The client type itself is represented as a template param, not sizeof(T)
  *  - In gdb, if you ask "whatis sFooStorage" you get (on ARM):
  *  (gdb) whatis sFooStorage
  *  nl::AlignedVarPool<Foo, 1ul, unsigned long long>
  *  This tells you there is [storage for] one object instance of Foo type, in
  *  a buffer aligned to uint64_t width. If you were using DEFINE_ALIGNED_VAR:
  *  (gdb) whatis sBarStorage
  *  uint64_t[12]
  *  - Printing such objects from GDB can be scripted using python, but even
  *  without a pretty-printer you can still just cast the memory used as a
  *  T* like you can with DEFINE_ALIGNED_VAR.
  **/

template< typename T, size_t Nct = 1, typename Talign = uint64_t >
class AlignedVarPool
{
public:
    /** Returns number of T objects with allocated space */
    size_t Count() const
    {
        return Nct;
    }
    /** Returns client size of all T objects -- useful bytes allocated in Buffer */
    size_t Size() const
    {
        return sizeof(T) * Nct;
    }
    /** Returns the bare buffer used for storing instances. This has to
        return a char* to avoid type-punning warnings about what we do here. */
    char* Buffer()
    {
        return reinterpret_cast<char*>(&mBufferPool[0]);
    }
    /** Returns the size of the buffer pool allocated, includes potentially some
        padding since the alignment type may be larger than the sizeof(T)
        Extent() - Size() == potentially unnecessary padding */
    size_t Extent() const
    {
        return sizeof(mBufferPool);
    }
    /** Returns the size of each element in the storage pool */
    size_t ElementSize() const
    {
        return sizeof(T);
    }
    /** Returns the alignment size of the Talign type used */
    size_t Alignment() const
    {
        return sizeof(Talign);
    }
    /** Retrieve instance inside pool. There is no check for value ranges. */
    T *Get(size_t aIndex = 0)
    {
        return &(reinterpret_cast<T*>(Buffer())[aIndex]);
    }
    const T *Get(size_t aIndex = 0) const
    {
        return Get(aIndex);
    }
    /** Casting operator to pointer of type T, used to drop-in replace objects
        of this type with the same kind of static array pointer you'd get from
        making mBufferPool explicitly, but also checking type. */
    operator T*()
    {
        return Get(0);
    }
    operator const T*() const
    {
        return Get(0);
    }
    /** Casting operator to reference of type T, convenience */
    operator T&()
    {
        return *Get(0);
    }
    operator const T&() const
    {
        return *Get(0);
    }
    /** For instances where Nct > 1, the standard array dereference operator
        could be implemented as an alias for Get(i) but in fact the casting
        operators above make this ambiguous; and in effect, ((T*)pool)[i] is
        the same effective result as implementing operator [] anyway. */
#if _EXAMPLE_IMPLEMENT_ARRAY_DEREF_CAUSES_WARNINGS
    T& operator [](size_t aIndex)
    {
        return *Get(aIndex);
    }
    const T& operator [](size_t aIndex) const
    {
        return *Get(aIndex);
    }
#endif
    /** Constructing and destructing arrays relies on some interesting C++
        behavior that is abstracted and implemented with static knowledge of the
        array size by these functions. Additionally, you can use the range-
        specific versions to construct just objects used rather than the
        new [] behavior of constructing all objects in the array at once. */

    /** Construct: Call default empty constructor for objects of type T on
        range of objects in pool, default range is one element at index 0.
        For pools where Nct == 1, this is equivalent to directly calling
        placement new() on the storage. */
    void Construct(size_t aFirstIndex = 0, size_t aCount = 1)
    {
        const size_t endIndex = aFirstIndex + aCount;
        for (size_t eachObjectIndex = aFirstIndex; eachObjectIndex < endIndex; ++eachObjectIndex)
        {
            new (Get(eachObjectIndex)) T();
        }
    }
    /** ConstructAll: Call default empty constructor for objects of type T on
        all objects in pool. */
    void ConstructAll()
    {
        Construct(0, Nct);
    }
    /** CopyConstruct: Call copy constructor from an initialized instance on range
        of objects in pool. The default range is one object at index 0. */
    void CopyConstruct(const T& aInitializer, size_t aFirstIndex = 0, size_t aCount = 1)
    {
        const size_t endIndex = aFirstIndex + aCount;

        for (size_t eachObjectIndex = aFirstIndex; eachObjectIndex < endIndex; ++eachObjectIndex)
        {
            new (Get(eachObjectIndex)) T(aInitializer);
        }
    }
    /** CopyConstructAll: Call copy constructor from a template instance on all
        objects in pool. */
    void CopyConstructAll(const T& aInitializer)
    {
        return CopyConstruct(aInitializer, 0, Nct);
    }
    /** Destruct: Call destructors on range of objects in pool. Default range
        is one object at default index 0. C++ destroys arrays in reverse order
        with delete [] so we do too. */
    void Destruct(size_t aFirstIndex = 0, size_t aCount = 1)
    {
        size_t eachObjectReverseIndex = aFirstIndex + aCount;

        while (eachObjectReverseIndex > aFirstIndex)
        {
            --eachObjectReverseIndex;
            T* eachObject = Get(eachObjectReverseIndex);
            (*eachObject).~T();
        }
    }
    /** DestructAll: Call destructors on all objects in pool. */
    void DestructAll()
    {
        Destruct(0, Nct);
    }
    /** Fill: Fill storage for range of objects with byte pattern. Default
        pattern is all 0 bytes. Default range is one object long at index 0. */
    void Fill(uint8_t aFillValue = 0, size_t aFirstIndex = 0, size_t aCount = 1)
    {
        memset(Get(aFirstIndex), aFillValue, sizeof(T) * aCount);
    }
    /** FillAll: Fill storage for entire range of objects with byte pattern.
        Default byte pattern is all 0 bytes. */
    void FillAll(uint8_t aFillValue = 0)
    {
        Fill(aFillValue, 0, Nct);
    }

private:
    static const size_t kPoolElements = (sizeof(T) * Nct + (sizeof(Talign) - 1))
                                        / sizeof(Talign);
    /** No constructor is run here, unless the user specified a non-POD C++ class
        for Talign. It's not clear why you would do that, though I can imagine
        a few very complicated and hard to justify reasons. */
    Talign mBufferPool[kPoolElements];
};

} // end namespace nl

#endif // NLUTILITIES_NLALIGNEDVARPOOL_HPP
