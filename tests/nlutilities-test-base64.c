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
 *      base64 encoding and decoding interfaces.
 *
 */

#include <nlbase64.h>

#include <string.h>

#include <nlunit-test.h>

static void TestBase64BlockEncoding(nlTestSuite *inSuite, void *inContext)
{
    const char *input1 = "The quick brown fox jumped over the lazy dog!";
    const char *expected_output1 = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgbGF6eSBkb2ch";
    const uint8_t input2[] = { 0xfc, 0x24, 0x57, 0xd0,
                               0x94, 0x20, 0x0f, 0xe4,
                               0x1a, 0xdf, 0x95, 0x4f,
                               0x49, 0x21, 0xed, 0x6f };
    const char *expected_output2 = "/CRX0JQgD+Qa35VPSSHtbw==";
    const uint8_t input3[] = { 'A' };
    const char *expected_output3 = "QQ==";
    const uint8_t input4[] = { 'A', 'B' };
    const char *expected_output4 = "QUI=";
    char output[128];
    uint16_t result;
    int n;

    result = nl_base64_encode((const uint8_t *)input1, strlen(input1), &output[0]);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output1));
    n = strncmp(&output[0], &expected_output1[0], strlen(&expected_output1[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = nl_base64_encode(input2, sizeof (input2) / sizeof (input2[0]), &output[0]);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output2));
    n = strncmp(&output[0], &expected_output2[0], strlen(&expected_output2[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = nl_base64_encode(input3, sizeof (input3) / sizeof (input3[0]), &output[0]);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output3));
    n = strncmp(&output[0], &expected_output3[0], strlen(&expected_output3[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = nl_base64_encode(input4, sizeof (input4) / sizeof (input4[0]), &output[0]);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output4));
    n = strncmp(&output[0], &expected_output4[0], strlen(&expected_output4[0]));
    NL_TEST_ASSERT(inSuite, n == 0);
}

static void TestBase64BlockDecoding(nlTestSuite *inSuite, void *inContext)
{
    const char *input1 = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgbGF6eSBkb2ch";
    const char *expected_output1 = "The quick brown fox jumped over the lazy dog!";
    const char *input2 = "/CRX0JQgD+Qa35VPSSHtbw==";
    const uint8_t expected_output2[] = { 0xfc, 0x24, 0x57, 0xd0,
                                         0x94, 0x20, 0x0f, 0xe4,
                                         0x1a, 0xdf, 0x95, 0x4f,
                                         0x49, 0x21, 0xed, 0x6f };
    const char *input3 = "|";
    const char *input4 = "||";
    const char *input5 = "{}|";
    uint8_t output[128];
    uint16_t result;
    int n;

    /* Positive Tests */

    result = nl_base64_decode(input1, strlen(input1), &output[0]);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output1));
    n = strncmp((const char *)&output[0], &expected_output1[0], strlen(&expected_output1[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = nl_base64_decode(input2, strlen(input2), &output[0]);
    NL_TEST_ASSERT(inSuite, result == sizeof (expected_output2) / sizeof (expected_output2[0]));
    n = memcmp(&output[0], &expected_output2[0], sizeof (expected_output2) / sizeof (expected_output2[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    /* Negative Tests */

    result = nl_base64_decode(input3, strlen(input3), &output[0]);
    NL_TEST_ASSERT(inSuite, result == UINT16_MAX);

    result = nl_base64_decode(input4, strlen(input4), &output[0]);
    NL_TEST_ASSERT(inSuite, result == UINT16_MAX);

    result = nl_base64_decode(input5, strlen(input5), &output[0]);
    NL_TEST_ASSERT(inSuite, result == UINT16_MAX);
}

struct Base64StreamPutcharContext
{
    char *output;
};

static void Base64StreamPutchar(const uint8_t inByte, void *inContext)
{
    struct Base64StreamPutcharContext *context = (struct Base64StreamPutcharContext *)(inContext);

    *(context->output)++ = inByte;
}

static uint8_t Base64StreamEncode(const uint8_t *inData, size_t inSize, char *outEncoding, bool inPad)
{
    struct Base64StreamPutcharContext context = { outEncoding };
    nl_base64_stream_enc_state_t state;
    uint8_t retval;

    nl_base64_stream_enc_start(&state, Base64StreamPutchar, &context);

    nl_base64_stream_enc_more(inData, inSize, &state);

    retval = nl_base64_stream_enc_finish(inPad, &state);

    return (retval);
}

static void TestBase64StreamEncoding(nlTestSuite *inSuite, void *inContext)
{
    const bool pad = true;
    const char *input1 = "The quick brown fox jumped over the lazy dog!";
    const char *expected_output1 = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgbGF6eSBkb2ch";
    const uint8_t input2[] = { 0xfc, 0x24, 0x57, 0xd0,
                               0x94, 0x20, 0x0f, 0xe4,
                               0x1a, 0xdf, 0x95, 0x4f,
                               0x49, 0x21, 0xed, 0x6f };
    const char *expected_output2 = "/CRX0JQgD+Qa35VPSSHtbw==";
    const uint8_t input3[] = { 'A' };
    const char *expected_output3 = "QQ==";
    const uint8_t input4[] = { 'A', 'B' };
    const char *expected_output4 = "QUI=";
    char output[128];
    uint8_t result;
    int n;

    /* With Padding */

    result = Base64StreamEncode((const uint8_t *)input1, strlen(input1), &output[0], pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output1));
    n = strncmp(&output[0], &expected_output1[0], strlen(&expected_output1[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = Base64StreamEncode(input2, sizeof (input2) / sizeof (input2[0]), &output[0], pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output2));
    n = strncmp(&output[0], &expected_output2[0], strlen(&expected_output2[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = Base64StreamEncode(input3, sizeof (input3) / sizeof (input3[0]), &output[0], pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output3));
    n = strncmp(&output[0], &expected_output3[0], strlen(&expected_output3[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = Base64StreamEncode(input4, sizeof (input4) / sizeof (input4[0]), &output[0], pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output4));
    n = strncmp(&output[0], &expected_output4[0], strlen(&expected_output4[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    /* Without Padding */

    result = Base64StreamEncode((const uint8_t *)input1, strlen(input1), &output[0], !pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output1));
    n = strncmp(&output[0], &expected_output1[0], strlen(&expected_output1[0]));
    NL_TEST_ASSERT(inSuite, n == 0);

    result = Base64StreamEncode(input2, sizeof (input2) / sizeof (input2[0]), &output[0], !pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output2) - 2);
    n = strncmp(&output[0], &expected_output2[0], strlen(&expected_output2[0]) - 2);
    NL_TEST_ASSERT(inSuite, n == 0);

    result = Base64StreamEncode(input3, sizeof (input3) / sizeof (input3[0]), &output[0], !pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output3) - 2);
    n = strncmp(&output[0], &expected_output3[0], strlen(&expected_output3[0]) - 2);
    NL_TEST_ASSERT(inSuite, n == 0);

    result = Base64StreamEncode(input4, sizeof (input4) / sizeof (input4[0]), &output[0], !pad);
    NL_TEST_ASSERT(inSuite, result == strlen(expected_output4) - 1);
    n = strncmp(&output[0], &expected_output4[0], strlen(&expected_output4[0]) - 1);
    NL_TEST_ASSERT(inSuite, n == 0);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("base64 block encoding",  TestBase64BlockEncoding),
    NL_TEST_DEF("base64 block decoding",  TestBase64BlockDecoding),
    NL_TEST_DEF("base64 stream encoding", TestBase64StreamEncoding),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-base64",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
