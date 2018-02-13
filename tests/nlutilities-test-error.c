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
 *      This file implements a unit test for Nest Labs Utilities
 *      status and error code interfaces.
 *
 */

#include <nlerror.h>

#include <nlassert.h>
#include <nlunit-test.h>

nlSTATIC_ASSERT(sizeof(nlError) == sizeof(int32_t));

static void TestErrorNegate(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    result = nlErrorNegate(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorNegate(1);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nlErrorNegate(-1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = nlErrorNegate(INT8_MIN);
    NL_TEST_ASSERT(inSuite, result == INT8_MAX + 1);

    result = nlErrorNegate(INT8_MAX);
    NL_TEST_ASSERT(inSuite, result == INT8_MIN + 1);

    result = nlErrorNegate(INT16_MIN);
    NL_TEST_ASSERT(inSuite, result == INT16_MAX + 1);

    result = nlErrorNegate(INT16_MAX);
    NL_TEST_ASSERT(inSuite, result == INT16_MIN + 1);
}

static void TestErrorCode(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    /* Constants */

    NL_TEST_ASSERT(inSuite, nlErrorCodeBits  == 16);
    NL_TEST_ASSERT(inSuite, nlErrorCodeMask  == 0xFFFF);
    NL_TEST_ASSERT(inSuite, nlErrorCodeShift == 0);
    NL_TEST_ASSERT(inSuite, nlErrorCodeMin   == 0);
    NL_TEST_ASSERT(inSuite, nlErrorCodeMax   == 65535);

    /* Encoding */

    result = nlErrorCodeEncode(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorCodeEncode(1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = nlErrorCodeEncode(INT8_MAX);
    NL_TEST_ASSERT(inSuite, result == INT8_MAX);

    result = nlErrorCodeEncode(UINT8_MAX);
    NL_TEST_ASSERT(inSuite, result == UINT8_MAX);

    result = nlErrorCodeEncode(INT16_MAX);
    NL_TEST_ASSERT(inSuite, result == INT16_MAX);

    result = nlErrorCodeEncode(UINT16_MAX);
    NL_TEST_ASSERT(inSuite, result == UINT16_MAX);

    result = nlErrorCodeEncode(INT32_MAX);
    NL_TEST_ASSERT(inSuite, result == UINT16_MAX);

    result = nlErrorCodeEncode(UINT32_MAX);
    NL_TEST_ASSERT(inSuite, result == UINT16_MAX);

    /* Decoding */

    result = nlErrorCodeDecode(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorCodeDecode(-1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = nlErrorCodeDecode(INT8_MIN);
    NL_TEST_ASSERT(inSuite, result == INT8_MAX + 1);

    result = nlErrorCodeDecode(INT16_MIN);
    NL_TEST_ASSERT(inSuite, result == INT16_MAX + 1);
}

static void TestErrorSubComponent(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    NL_TEST_ASSERT(inSuite, nlErrorSubComponentBits  == 12);
    NL_TEST_ASSERT(inSuite, nlErrorSubComponentMask  == 0xFFF);
    NL_TEST_ASSERT(inSuite, nlErrorSubComponentShift == nlErrorCodeBits);
    NL_TEST_ASSERT(inSuite, nlErrorSubComponentMin   == 0);
    NL_TEST_ASSERT(inSuite, nlErrorSubComponentMax   == 4095);

    /* Encoding */

    result = nlErrorSubComponentEncode(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorSubComponentEncode(1);
    NL_TEST_ASSERT(inSuite, result == 0x10000);

    result = nlErrorSubComponentEncode(INT8_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x7F0000);

    result = nlErrorSubComponentEncode(UINT8_MAX);
    NL_TEST_ASSERT(inSuite, result == 0xFF0000);

    result = nlErrorSubComponentEncode(INT16_MAX);
    NL_TEST_ASSERT(inSuite, result == 0xFFF0000);

    result = nlErrorSubComponentEncode(UINT16_MAX);
    NL_TEST_ASSERT(inSuite, result == 0xFFF0000);

    result = nlErrorSubComponentEncode(INT32_MAX);
    NL_TEST_ASSERT(inSuite, result == 0xFFF0000);

    result = nlErrorSubComponentEncode(UINT32_MAX);
    NL_TEST_ASSERT(inSuite, result == 0xFFF0000);

    /* Decoding */

    result = nlErrorSubComponentDecode(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorSubComponentDecode(-65536);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = nlErrorSubComponentDecode(-131072);
    NL_TEST_ASSERT(inSuite, result == 2);

    result = nlErrorSubComponentDecode(-134152192);
    NL_TEST_ASSERT(inSuite, result == 2047);

    result = nlErrorSubComponentDecode(-268369920);
    NL_TEST_ASSERT(inSuite, result == 4095);
}

static void TestErrorComponent(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    NL_TEST_ASSERT(inSuite, nlErrorComponentBits  == 3);
    NL_TEST_ASSERT(inSuite, nlErrorComponentMask  == 0x7);
    NL_TEST_ASSERT(inSuite, nlErrorComponentShift == (nlErrorCodeBits + nlErrorSubComponentBits));
    NL_TEST_ASSERT(inSuite, nlErrorComponentMin   == 0);
    NL_TEST_ASSERT(inSuite, nlErrorComponentMax   == 7);

    /* Encoding */

    result = nlErrorComponentEncode(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorComponentEncode(1);
    NL_TEST_ASSERT(inSuite, result == 0x10000000);

    result = nlErrorComponentEncode(INT8_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x70000000);

    result = nlErrorComponentEncode(UINT8_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x70000000);

    result = nlErrorComponentEncode(INT16_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x70000000);

    result = nlErrorComponentEncode(UINT16_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x70000000);

    result = nlErrorComponentEncode(INT32_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x70000000);

    result = nlErrorComponentEncode(UINT32_MAX);
    NL_TEST_ASSERT(inSuite, result == 0x70000000);

    /* Decoding */

    result = nlErrorComponentDecode(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorComponentDecode(-268435456);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = nlErrorComponentDecode(-536870912);
    NL_TEST_ASSERT(inSuite, result == 2);

    result = nlErrorComponentDecode(-805306368);
    NL_TEST_ASSERT(inSuite, result == 3);

    result = nlErrorComponentDecode(-1879048192);
    NL_TEST_ASSERT(inSuite, result == 7);
}

static void TestErrorMacro(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    result = nlERROR(0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlERROR(1);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nlERROR(-1);
    NL_TEST_ASSERT(inSuite, result == 1);

    result = nlERROR(INT8_MIN);
    NL_TEST_ASSERT(inSuite, result == INT8_MAX + 1);

    result = nlERROR(INT8_MAX);
    NL_TEST_ASSERT(inSuite, result == INT8_MIN + 1);

    result = nlERROR(INT16_MIN);
    NL_TEST_ASSERT(inSuite, result == INT16_MAX + 1);

    result = nlERROR(INT16_MAX);
    NL_TEST_ASSERT(inSuite, result == INT16_MIN + 1);
}

static void TestErrorComposition(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    result = nlErrorCompose(0, 0, 0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorCompose(1, 0, 0);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nlErrorCompose(0, 1, 0);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nlErrorCompose(0, 0, 1);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nlErrorCompose(0x7, 0, 0);
    NL_TEST_ASSERT(inSuite, result == -7);

    result = nlErrorCompose(0x0, 0x7FF, 0);
    NL_TEST_ASSERT(inSuite, result == -2047);

    result = nlErrorCompose(0x0, 0x0, 0x7FFF);
    NL_TEST_ASSERT(inSuite, result == -32767);

    result = nlErrorCompose(0x7, 0xFFF, 0xFFFF);
    NL_TEST_ASSERT(inSuite, result == -65535);
}

static void TestErrorEncoding(nlTestSuite *inSuite, void *inContext)
{
    nlError result;

    result = nlErrorEncode(0, 0, 0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nlErrorEncode(1, 0, 0);
    NL_TEST_ASSERT(inSuite, result == -268435456);

    result = nlErrorEncode(0, 1, 0);
    NL_TEST_ASSERT(inSuite, result == -65536);

    result = nlErrorEncode(0, 0, 1);
    NL_TEST_ASSERT(inSuite, result == -1);

    result = nlErrorEncode(0x7, 0, 0);
    NL_TEST_ASSERT(inSuite, result == -1879048192);

    result = nlErrorEncode(0x0, 0x7FF, 0);
    NL_TEST_ASSERT(inSuite, result == -134152192);

    result = nlErrorEncode(0x0, 0x0, 0x7FFF);
    NL_TEST_ASSERT(inSuite, result == -32767);

    result = nlErrorEncode(0x7, 0xFFF, 0xFFFF);
    NL_TEST_ASSERT(inSuite, result == -2147483647);
}

static void TestErrorIntrospection(nlTestSuite *inSuite, void *inContext)
{
    bool result;

    result = nlErrorIs(0, 0, 0);
    NL_TEST_ASSERT(inSuite, result == true);

    result = nlErrorIs(0, 0, -32767);
    NL_TEST_ASSERT(inSuite, result == true);

    result = nlErrorIs(1, 1, -32767);
    NL_TEST_ASSERT(inSuite, result == false);
}

static void TestErrorSuccess(nlTestSuite *inSuite, void *inContext)
{
    NL_TEST_ASSERT(inSuite, nlSUCCESS == 0);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("error negation",                   TestErrorNegate),
    NL_TEST_DEF("error code encode/decode",         TestErrorCode),
    NL_TEST_DEF("error subcomponent encode/decode", TestErrorSubComponent),
    NL_TEST_DEF("error component encode/decode",    TestErrorComponent),
    NL_TEST_DEF("error macro",                      TestErrorMacro),
    NL_TEST_DEF("error composition",                TestErrorComposition),
    NL_TEST_DEF("error encoding",                   TestErrorEncoding),
    NL_TEST_DEF("error introspection",              TestErrorIntrospection),
    NL_TEST_DEF("error success",                    TestErrorSuccess),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-error",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
