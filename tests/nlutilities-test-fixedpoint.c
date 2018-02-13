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
 *      fixed point math interfaces.
 *
 */

#include <nlfixedpoint.h>

#include <nlunit-test.h>

static void TestIntToFixed(nlTestSuite *inSuite, void *inContext)
{
    int32_t  rs32;
    uint32_t ru32;
    size_t   i;
    int      retval;

    /* Negative Tests */

    // Desired bits out of range

    retval = nl_int16_to_fixed32(NULL, 0, 0, 32);
    NL_TEST_ASSERT(inSuite, retval == -1);

    retval = nl_uint16_to_fixed32(NULL, 0, 0, 32);
    NL_TEST_ASSERT(inSuite, retval == -1);

    retval = nl_int32_to_fixed32(NULL, 0, 0, 32);
    NL_TEST_ASSERT(inSuite, retval == -1);

    retval = nl_uint32_to_fixed32(NULL, 0, 0, 32);
    NL_TEST_ASSERT(inSuite, retval == -1);

    // Resulting value out of range

    retval = nl_int16_to_fixed32(&rs32, INT16_MAX, UINT32_MAX, 31);
    NL_TEST_ASSERT(inSuite, retval == -1);

    retval = nl_uint16_to_fixed32(&ru32, UINT16_MAX, UINT32_MAX, 31);
    NL_TEST_ASSERT(inSuite, retval == -1);

    retval = nl_int32_to_fixed32(&rs32, INT32_MAX, UINT32_MAX, 31);
    NL_TEST_ASSERT(inSuite, retval == -1);

    retval = nl_uint32_to_fixed32(&ru32, UINT32_MAX, UINT32_MAX, 31);
    NL_TEST_ASSERT(inSuite, retval == -1);

    /* Positive Tests */

    // Zero (0) scale value should yield a zero (0) result

    retval = nl_int16_to_fixed32(&rs32, INT16_MAX, 0, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    retval = nl_uint16_to_fixed32(&ru32, UINT16_MAX, 0, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    retval = nl_int32_to_fixed32(&rs32, INT32_MAX, 0, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    retval = nl_uint32_to_fixed32(&ru32, UINT32_MAX, 0, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    // Zero (0) value should yield a zero (0) result. 

    retval = nl_int16_to_fixed32(&rs32, 0, 1, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    retval = nl_uint16_to_fixed32(&ru32, 0, 1, 15);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    retval = nl_int32_to_fixed32(&rs32, 0, 1, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0);

    retval = nl_uint32_to_fixed32(&ru32, 0, 1, 0);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, ru32 == 0);

    // Regardless of the fractional bits, 1 scaled by 1 should always be 1.

    for (i = 0; i < 32; i++)
    {
        retval = nl_int16_to_fixed32(&rs32, 1, 1, i);
        NL_TEST_ASSERT(inSuite, retval == 0);
        NL_TEST_ASSERT(inSuite, rs32 == 1);

        retval = nl_uint16_to_fixed32(&ru32, 1, 1, i);
        NL_TEST_ASSERT(inSuite, retval == 0);
        NL_TEST_ASSERT(inSuite, ru32 == 1);

        retval = nl_int32_to_fixed32(&rs32, 1, 1, i);
        NL_TEST_ASSERT(inSuite, retval == 0);
        NL_TEST_ASSERT(inSuite, rs32 == 1);

        retval = nl_uint32_to_fixed32(&ru32, 1, 1, i);
        NL_TEST_ASSERT(inSuite, retval == 0);
        NL_TEST_ASSERT(inSuite, ru32 == 1);
    }
}

static const nlTest sTests[] = {
    NL_TEST_DEF("integer to fixed conversion", TestIntToFixed),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-fixedpoint",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
