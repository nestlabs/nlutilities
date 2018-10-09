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
 *      abs variants.
 *
 */

#include <nlabs-variants.h>

#include <stdint.h>
#include <limits.h>

#include <nlunit-test.h>

static void TestAbsUint(nlTestSuite *inSuite, void *inContext)
{
    uintmax_t result;

    result = abs_uint(INT_MIN);
    NL_TEST_ASSERT(inSuite, result == -INT_MIN);

    result = abs_uint(-1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = abs_uint(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = abs_uint(1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = abs_uint(INT_MAX);
    NL_TEST_ASSERT(inSuite, result == INT_MAX);
}

static void TestAbsApprox(nlTestSuite *inSuite, void *inContext)
{
    intmax_t result;

    result = abs_approx(INT_MIN);
    NL_TEST_ASSERT(inSuite, result == INT_MAX);

    result = abs_approx(-1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = abs_approx(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = abs_approx(1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = abs_approx(INT_MAX);
    NL_TEST_ASSERT(inSuite, result == INT_MAX);
}

static void TestNabs(nlTestSuite *inSuite, void *inContext)
{
    intmax_t result;

    result = nabs(INT_MIN);
    NL_TEST_ASSERT(inSuite, result == INT_MIN);

    result = nabs(-1);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nabs(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nabs(1);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nabs(INT_MAX);
    NL_TEST_ASSERT(inSuite, result == -INT_MAX);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("abs abs_uint",   TestAbsUint),
    NL_TEST_DEF("abs abs_approx", TestAbsApprox),
    NL_TEST_DEF("abs nabs",       TestNabs),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-abs",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
