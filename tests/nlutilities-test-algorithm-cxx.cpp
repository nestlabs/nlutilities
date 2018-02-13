/*
 *
 *    Copyright (c) 2018 Nest Labs, Inc.
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
 *      This file implements a unit test for the Nest Labs Utilities
 *      C++ algorithm template interfaces.
 *
 */

#include <nlalgorithm.hpp>

#include <stdint.h>

#include <nlunit-test.h>

class Integer
{
public:
    Integer(void) : mValue(0) { return; }
    Integer(const int32_t &inValue) : mValue(inValue) { return; }

    Integer &operator =(const int32_t &inValue) { mValue = inValue; return *this; }

    bool operator <(const Integer &inInteger) const { return (mValue < inInteger.mValue); }
    bool operator ==(const int32_t &inValue) const { return (mValue == inValue); }

private:
    int32_t mValue;
};

static void TestMin(nlTestSuite *inSuite, void *inContext)
{
    int32_t as32, bs32, rs32;
    uint32_t au32, bu32, ru32;
    Integer aInteger, bInteger, rInteger;

    /* Signed 32-bit vs. Signed 32-bit */

    as32 = 0;
    bs32 = 0;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    as32 = 0;
    bs32 = 1;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    as32 = 1;
    bs32 = 0;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    as32 = 0;
    bs32 = -1;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == -1);

    as32 = -1;
    bs32 = 0;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == -1);

    as32 = INT32_MIN;
    bs32 = 0;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MIN);

    as32 = 0;
    bs32 = INT32_MIN;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MIN);

    as32 = INT32_MAX;
    bs32 = 0;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    as32 = 0;
    bs32 = INT32_MAX;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    as32 = INT32_MIN;
    bs32 = INT32_MAX;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MIN);

    as32 = INT32_MAX;
    bs32 = INT32_MIN;
    rs32 = nl::min(as32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MIN);

    /* Unsigned 32-bit vs. Unsigned 32-bit */

    au32 = 0;
    bu32 = 0;
    ru32 = nl::min(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    au32 = 0;
    bu32 = 1;
    ru32 = nl::min(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    au32 = 1;
    bu32 = 0;
    ru32 = nl::min(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    au32 = UINT32_MAX;
    bu32 = 0;
    ru32 = nl::min(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    au32 = 0;
    bu32 = UINT32_MAX;
    ru32 = nl::min(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    /* Non-POD type vs. Non-POD type */

    aInteger = 0;
    bInteger = 0;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = 0;
    bInteger = 1;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = 1;
    bInteger = 0;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = 0;
    bInteger = -1;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == -1);

    aInteger = -1;
    bInteger = 0;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == -1);

    aInteger = INT32_MIN;
    bInteger = 0;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MIN);

    aInteger = 0;
    bInteger = INT32_MIN;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MIN);

    aInteger = INT32_MAX;
    bInteger = 0;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = 0;
    bInteger = INT32_MAX;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = INT32_MIN;
    bInteger = INT32_MAX;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MIN);

    aInteger = INT32_MAX;
    bInteger = INT32_MIN;
    rInteger = nl::min(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MIN);
}

static void TestMax(nlTestSuite *inSuite, void *inContext)
{
    int32_t ls32, bs32, rs32;
    uint32_t au32, bu32, ru32;
    Integer aInteger, bInteger, rInteger;

    /* Signed 32-bit vs. Signed 32-bit */

    ls32 = 0;
    bs32 = 0;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    ls32 = 0;
    bs32 = 1;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 1);

    ls32 = 1;
    bs32 = 0;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 1);

    ls32 = 0;
    bs32 = -1;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    ls32 = -1;
    bs32 = 0;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    ls32 = INT32_MIN;
    bs32 = 0;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    ls32 = 0;
    bs32 = INT32_MIN;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    ls32 = INT32_MAX;
    bs32 = 0;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MAX);

    ls32 = 0;
    bs32 = INT32_MAX;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MAX);

    ls32 = INT32_MIN;
    bs32 = INT32_MAX;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MAX);

    ls32 = INT32_MAX;
    bs32 = INT32_MIN;
    rs32 = nl::max(ls32, bs32);
    NL_TEST_ASSERT(inSuite, rs32 == INT32_MAX);

    /* Unsigned 32-bit vs. Unsigned 32-bit */

    au32 = 0;
    bu32 = 0;
    ru32 = nl::max(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    au32 = 0;
    bu32 = 1;
    ru32 = nl::max(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 1);

    au32 = 1;
    bu32 = 0;
    ru32 = nl::max(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == 1);

    au32 = UINT32_MAX;
    bu32 = 0;
    ru32 = nl::max(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == UINT32_MAX);

    au32 = 0;
    bu32 = UINT32_MAX;
    ru32 = nl::max(au32, bu32);
    NL_TEST_ASSERT(inSuite, ru32 == UINT32_MAX);

    /* Non-POD type vs. Non-POD type */

    aInteger = 0;
    bInteger = 0;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = 0;
    bInteger = 1;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 1);

    aInteger = 1;
    bInteger = 0;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 1);

    aInteger = 0;
    bInteger = -1;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = -1;
    bInteger = 0;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = INT32_MIN;
    bInteger = 0;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = 0;
    bInteger = INT32_MIN;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    aInteger = INT32_MAX;
    bInteger = 0;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MAX);

    aInteger = 0;
    bInteger = INT32_MAX;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MAX);

    aInteger = INT32_MIN;
    bInteger = INT32_MAX;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MAX);

    aInteger = INT32_MAX;
    bInteger = INT32_MIN;
    rInteger = nl::max(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, rInteger == INT32_MAX);
}

static void TestClamp(nlTestSuite *inSuite, void *inContext)
{
    int32_t vs32, ls32, us32, rs32;
    uint32_t vu32, lu32, uu32, ru32;
    Integer vInteger, lInteger, uInteger, rInteger;

    /* Signed 32-bit */

    vs32 = 0;
    ls32 = 0;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 0;
    ls32 = 0;
    us32 = 1;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 0;
    ls32 = -1;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 1;
    ls32 = 0;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 1;
    ls32 = 0;
    us32 = 1;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 1);

    vs32 = 1;
    ls32 = -1;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = -1;
    ls32 = 0;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = -1;
    ls32 = 0;
    us32 = 1;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = -1;
    ls32 = -1;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == -1);

    vs32 = 2;
    ls32 = 0;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 2;
    ls32 = 0;
    us32 = 1;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 1);

    vs32 = 2;
    ls32 = -1;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 0;
    ls32 = INT32_MIN;
    us32 = 0;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 0;
    ls32 = 0;
    us32 = INT32_MAX;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    vs32 = 0;
    ls32 = INT32_MIN;
    us32 = INT32_MAX;
    rs32 = nl::clamp(vs32, ls32, us32);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    /* Unsigned 32-bit vs. Unsigned 32-bit */

    vu32 = 0;
    lu32 = 0;
    uu32 = 0;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    vu32 = 0;
    lu32 = 0;
    uu32 = 1;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    vu32 = 0;
    lu32 = 0;
    uu32 = UINT32_MAX;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    vu32 = 1;
    lu32 = 0;
    uu32 = 0;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    vu32 = 1;
    lu32 = 0;
    uu32 = 1;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 1);

    vu32 = 1;
    lu32 = 0;
    uu32 = UINT32_MAX;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 1);

    vu32 = 2;
    lu32 = 0;
    uu32 = 0;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    vu32 = 2;
    lu32 = 0;
    uu32 = 1;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 1);

    vu32 = 2;
    lu32 = 0;
    uu32 = UINT32_MAX;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 2);

    vu32 = UINT32_MAX;
    lu32 = 0;
    uu32 = 0;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    vu32 = UINT32_MAX;
    lu32 = 0;
    uu32 = 1;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == 1);

    vu32 = UINT32_MAX;
    lu32 = 0;
    uu32 = UINT32_MAX;
    ru32 = nl::clamp(vu32, lu32, uu32);
    NL_TEST_ASSERT(inSuite, ru32 == UINT32_MAX);

    /* Non-POD type vs. Non-POD type */

    vInteger = 0;
    lInteger = 0;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 0;
    lInteger = 0;
    uInteger = 1;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 0;
    lInteger = -1;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 1;
    lInteger = 0;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 1;
    lInteger = 0;
    uInteger = 1;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 1);

    vInteger = 1;
    lInteger = -1;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = -1;
    lInteger = 0;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = -1;
    lInteger = 0;
    uInteger = 1;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = -1;
    lInteger = -1;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == -1);

    vInteger = 2;
    lInteger = 0;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 2;
    lInteger = 0;
    uInteger = 1;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 1);

    vInteger = 2;
    lInteger = -1;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 0;
    lInteger = INT32_MIN;
    uInteger = 0;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 0;
    lInteger = 0;
    uInteger = INT32_MAX;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);

    vInteger = 0;
    lInteger = INT32_MIN;
    uInteger = INT32_MAX;
    rInteger = nl::clamp(vInteger, lInteger, uInteger);
    NL_TEST_ASSERT(inSuite, rInteger == 0);
}

static void TestSwap(nlTestSuite *inSuite, void *inContext)
{
    int32_t as32, bs32;
    uint32_t au32, bu32;
    Integer aInteger, bInteger;

    as32 = 0;
    bs32 = INT32_MAX;
    nl::swap(as32, bs32);
    NL_TEST_ASSERT(inSuite, as32 == INT32_MAX);
    NL_TEST_ASSERT(inSuite, bs32 == 0);

    au32 = UINT32_MAX;
    bu32 = 0;
    nl::swap(au32, bu32);
    NL_TEST_ASSERT(inSuite, au32 == 0);
    NL_TEST_ASSERT(inSuite, bu32 == UINT32_MAX);

    aInteger = 0;
    bInteger = INT32_MAX;
    nl::swap(aInteger, bInteger);
    NL_TEST_ASSERT(inSuite, aInteger == INT32_MAX);
    NL_TEST_ASSERT(inSuite, bInteger == 0);
}

static void TestIterSwap(nlTestSuite *inSuite, void *inContext)
{
    int32_t as32, bs32;
    uint32_t au32, bu32;
    Integer aInteger, bInteger;

    as32 = 0;
    bs32 = INT32_MAX;
    nl::iter_swap(&as32, &bs32);
    NL_TEST_ASSERT(inSuite, as32 == INT32_MAX);
    NL_TEST_ASSERT(inSuite, bs32 == 0);

    au32 = UINT32_MAX;
    bu32 = 0;
    nl::iter_swap(&au32, &bu32);
    NL_TEST_ASSERT(inSuite, au32 == 0);
    NL_TEST_ASSERT(inSuite, bu32 == UINT32_MAX);

    aInteger = 0;
    bInteger = INT32_MAX;
    nl::iter_swap(&aInteger, &bInteger);
    NL_TEST_ASSERT(inSuite, aInteger == INT32_MAX);
    NL_TEST_ASSERT(inSuite, bInteger == 0);
}

static void TestIterSwapRange(nlTestSuite *inSuite, void *inContext)
{
    int32_t as32[3] = { INT32_MIN, 0, INT32_MAX };
    uint32_t au32[3] = { 0, UINT32_MAX / 2, UINT32_MAX };
    Integer aInteger[3] = { INT32_MIN, 0, INT32_MAX };

    nl::iter_swap_range(&as32[0], &as32[2]);
    NL_TEST_ASSERT(inSuite, as32[0] == 0);
    NL_TEST_ASSERT(inSuite, as32[1] == INT32_MAX);
    NL_TEST_ASSERT(inSuite, as32[2] == INT32_MIN);

    nl::iter_swap_range(&au32[0], &au32[2]);
    NL_TEST_ASSERT(inSuite, au32[0] == UINT32_MAX / 2);
    NL_TEST_ASSERT(inSuite, au32[1] == UINT32_MAX);
    NL_TEST_ASSERT(inSuite, au32[2] == 0);

    nl::iter_swap_range(&aInteger[0], &aInteger[2]);
    NL_TEST_ASSERT(inSuite, aInteger[0] == 0);
    NL_TEST_ASSERT(inSuite, aInteger[1] == INT32_MAX);
    NL_TEST_ASSERT(inSuite, aInteger[2] == INT32_MIN);
}


static const nlTest sTests[] = {
    NL_TEST_DEF("min",                 TestMin),
    NL_TEST_DEF("max",                 TestMax),
    NL_TEST_DEF("clamp",               TestClamp),
    NL_TEST_DEF("reference swap",      TestSwap),
    NL_TEST_DEF("iterator swap",       TestIterSwap),
    NL_TEST_DEF("iterator range swap", TestIterSwapRange),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-algorithm",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
