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
 *      preprocessor macro interfaces.
 *
 */

#include <nlmacros.h>

#include <nlunit-test.h>

struct offset_of_test_s
{
    uint8_t                      m_first;
    uint8_t                      m_second[3];
    uint16_t                     m_third[2];
    uint32_t                     m_fourth[2];
    uint64_t                     m_fifth;
    struct offset_of_test_s *    m_sixth;
};

typedef struct offset_of_test_s offset_of_test_t;

typedef struct link_test_s link_test_t;

struct link_test_s
{
    link_test_t *link;
};

struct container_of_test_s
{
    uint8_t                      m_first;
    uint8_t                      m_second;
    uint8_t                      m_third;
    uint8_t                      m_fourth;
    uint32_t                     m_fifth;
    link_test_t                  m_link;
};

typedef struct container_of_test_s container_of_test_t;

static void TestMacrosOffsetOf(nlTestSuite *inSuite, void *inContext)
{
    size_t offset;

    offset = OFFSETOF(offset_of_test_t, m_first);
    NL_TEST_ASSERT(inSuite, offset == 0);

    offset = OFFSETOF(offset_of_test_t, m_second);
    NL_TEST_ASSERT(inSuite, offset == 1);

    offset = OFFSETOF(offset_of_test_t, m_third);
    NL_TEST_ASSERT(inSuite, offset == 4);

    offset = OFFSETOF(offset_of_test_t, m_fourth);
    NL_TEST_ASSERT(inSuite, offset == 8);

    offset = OFFSETOF(offset_of_test_t, m_fifth);
    NL_TEST_ASSERT(inSuite, offset == 16);

    offset = OFFSETOF(offset_of_test_t, m_sixth);
    NL_TEST_ASSERT(inSuite, offset == 24);
}

static void TestMacrosContainerOf(nlTestSuite *inSuite, void *inContext)
{
    container_of_test_t a = { 1, 2, 3, 4, 5, { NULL } };
    container_of_test_t b = { 11, 12, 13, 14, 15, { &a.m_link } };
    container_of_test_t *ap, *bp;

    ap = CONTAINEROF(&a.m_link, container_of_test_t, m_link);
    NL_TEST_ASSERT(inSuite, ap == &a);

    bp = CONTAINEROF(&b.m_link, container_of_test_t, m_link);
    NL_TEST_ASSERT(inSuite, bp == &b);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("macros offsetof",                      TestMacrosOffsetOf),
    NL_TEST_DEF("macros containerof",                   TestMacrosContainerOf),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilites-macros",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
