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
 *      16-bit memset interface.
 *
 */

#include <nlmemset16.h>

#include <stdint.h>
#include <string.h>

#include <nlunit-test.h>

static uint16_t GetUnaligned16(uint16_t *inPointer)
{
    uint16_t temp;

    memcpy(&temp, inPointer, sizeof (uint16_t));

    return (temp);
}

static void TestMemset16(nlTestSuite *inSuite, void *inContext)
{
    uint16_t buffer1[1];
    uint16_t buffer2[2];
    uint16_t buffer8[8];
    uint16_t buffer10[10];
    uint16_t buffer17[17];
    uint8_t  buffer34[34];
    uint16_t *unaligned_p;

    /* 16-bit Aligned Buffers */

    nl_memset16(&buffer1[0], 0xAA55, 1);
    NL_TEST_ASSERT(inSuite, buffer1[0] == 0xAA55);

    nl_memset16(&buffer2[0], 0xCC33, 2);
    NL_TEST_ASSERT(inSuite, buffer2[0] == 0xCC33);
    NL_TEST_ASSERT(inSuite, buffer2[1] == 0xCC33);

    nl_memset16(&buffer8[0], 0x8888, 8);
    NL_TEST_ASSERT(inSuite, buffer8[0] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[1] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[2] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[3] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[4] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[5] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[6] == 0x8888);
    NL_TEST_ASSERT(inSuite, buffer8[7] == 0x8888);

    nl_memset16(&buffer10[0], 0x1010, 10);
    NL_TEST_ASSERT(inSuite, buffer10[0] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[1] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[2] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[3] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[4] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[5] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[6] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[7] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[8] == 0x1010);
    NL_TEST_ASSERT(inSuite, buffer10[9] == 0x1010);

    nl_memset16(&buffer17[0], 0x4242, 17);
    NL_TEST_ASSERT(inSuite, buffer17[0] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[1] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[2] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[3] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[4] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[5] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[6] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[7] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[8] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[9] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[10] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[11] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[12] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[13] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[14] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[15] == 0x4242);
    NL_TEST_ASSERT(inSuite, buffer17[16] == 0x4242);

    /* Unaligned Buffer */

    nl_memset16(&buffer34[1], 0x3434, 16);
    unaligned_p = (void *)&buffer34[1];
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[0]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[1]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[2]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[3]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[4]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[5]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[6]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[7]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[8]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[9]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[10]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[11]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[12]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[13]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[14]) == 0x3434);
    NL_TEST_ASSERT(inSuite, GetUnaligned16(&unaligned_p[15]) == 0x3434);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("memset16", TestMemset16),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-memset16",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
