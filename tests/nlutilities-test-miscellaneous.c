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
 *      This file implements unit tests for the Nest Labs Utilities
 *      miscellaneous interfaces.
 *
 */

#include <nlutilities.h>

#include <string.h>

#include <nlunit-test.h>

static void TestGetCharSeparatedBytes(nlTestSuite *inSuite, void *inContext)
{
    int retval;

    // good. 6 bytes MAC example
    const char mac[] = "18:b4:30:00:01:02";
    uint8_t bytes[8];
    retval = nl_getCharSeparatedBytes(&mac[0], &bytes[0], 6, ':', 16);
    NL_TEST_ASSERT(inSuite, retval == 6);
    NL_TEST_ASSERT(inSuite, bytes[0] == 0x18);
    NL_TEST_ASSERT(inSuite, bytes[1] == 0xb4);
    NL_TEST_ASSERT(inSuite, bytes[2] == 0x30);
    NL_TEST_ASSERT(inSuite, bytes[3] == 0x00);
    NL_TEST_ASSERT(inSuite, bytes[4] == 0x01);
    NL_TEST_ASSERT(inSuite, bytes[5] == 0x02);

    // good. 8 bytes MAC example
    const char longmac[] = "18:b4:30:ca:fe:ba:0b:ab";
    retval = nl_getCharSeparatedBytes(&longmac[0], &bytes[0], 8, ':', 16);
    NL_TEST_ASSERT(inSuite, retval == 8);
    NL_TEST_ASSERT(inSuite, bytes[0] == 0x18);
    NL_TEST_ASSERT(inSuite, bytes[1] == 0xb4);
    NL_TEST_ASSERT(inSuite, bytes[2] == 0x30);
    NL_TEST_ASSERT(inSuite, bytes[3] == 0xca);
    NL_TEST_ASSERT(inSuite, bytes[4] == 0xfe);
    NL_TEST_ASSERT(inSuite, bytes[5] == 0xba);
    NL_TEST_ASSERT(inSuite, bytes[6] == 0x0b);
    NL_TEST_ASSERT(inSuite, bytes[7] == 0xab);

    // good. 3 comma separated values
    const char csv1[] = "123,67,90";
    retval = nl_getCharSeparatedBytes(&csv1[0], &bytes[0], 3, ',', 10);
    NL_TEST_ASSERT(inSuite, retval == 3);
    NL_TEST_ASSERT(inSuite, bytes[0] == 123);
    NL_TEST_ASSERT(inSuite, bytes[1] == 67);
    NL_TEST_ASSERT(inSuite, bytes[2] == 90);

    // bad. 3 comma separated values, 1 out of range
    const char csv2[] = "123,67,450";
    retval = nl_getCharSeparatedBytes(&csv2[0], &bytes[0], 3, ',', 10);
    NL_TEST_ASSERT(inSuite, retval == 2);
    NL_TEST_ASSERT(inSuite, bytes[0] == 123);
    NL_TEST_ASSERT(inSuite, bytes[1] == 67);

    // bad. junk at the end
    const char error1[] = "18:b4:30:ca:fe:ba:0b:ab,";
    retval = nl_getCharSeparatedBytes(&error1[0], &bytes[0], 8, ':', 16);
    NL_TEST_ASSERT(inSuite, retval == 7);
    NL_TEST_ASSERT(inSuite, bytes[0] == 0x18);
    NL_TEST_ASSERT(inSuite, bytes[1] == 0xb4);
    NL_TEST_ASSERT(inSuite, bytes[2] == 0x30);
    NL_TEST_ASSERT(inSuite, bytes[3] == 0xca);
    NL_TEST_ASSERT(inSuite, bytes[4] == 0xfe);
    NL_TEST_ASSERT(inSuite, bytes[5] == 0xba);
    NL_TEST_ASSERT(inSuite, bytes[6] == 0x0b);

    // bad. too short
    const char error2[] = "18:b4:30:ca";
    retval = nl_getCharSeparatedBytes(&error2[0], &bytes[0], 6, ':', 16);
    NL_TEST_ASSERT(inSuite, retval == 3);
    NL_TEST_ASSERT(inSuite, bytes[0] == 0x18);
    NL_TEST_ASSERT(inSuite, bytes[1] == 0xb4);
    NL_TEST_ASSERT(inSuite, bytes[2] == 0x30);

    // bad. invalid separator
    const char error3[] = "18:b4:30;ca:ab:12";
    retval = nl_getCharSeparatedBytes(&error3[0], &bytes[0], 6, ':', 16);
    NL_TEST_ASSERT(inSuite, retval == 2);
    NL_TEST_ASSERT(inSuite, bytes[0] == 0x18);
    NL_TEST_ASSERT(inSuite, bytes[1] == 0xb4);

    // bad. garbage after separator
    const char error4[] = "18:b4:30:xca:ab:12";
    retval = nl_getCharSeparatedBytes(&error4[0], &bytes[0], 6, ':', 16);
    NL_TEST_ASSERT(inSuite, retval == 3);
    NL_TEST_ASSERT(inSuite, bytes[0] == 0x18);
    NL_TEST_ASSERT(inSuite, bytes[1] == 0xb4);
    NL_TEST_ASSERT(inSuite, bytes[2] == 0x30);
}

static void TestPrintBytesWithSeparator(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t bytes[4] = { 0x18, 0xb4, 0x30, 0x00 };

    nl_printBytesWithSeparator(&bytes[0], 4, ':');
}

static void TestHexToBin(nlTestSuite *inSuite, void *inContext)
{
    const char hex[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f' };
    const uint8_t expected_bin[22] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
    uint8_t bin[22];
    uint8_t result;
    size_t i;

    for (i = 0; i < 22; i++)
    {
        bin[i] = nl_hextobin(hex[i]);
        NL_TEST_ASSERT(inSuite, bin[i] == expected_bin[i]);
    }

    result = nl_hextobin('z');
    NL_TEST_ASSERT(inSuite, result == 'z');

    result = nl_hextobin('/');
    NL_TEST_ASSERT(inSuite, result == '/');

    result = nl_hextobin(':');
    NL_TEST_ASSERT(inSuite, result == ':');

    result = nl_hextobin('g');
    NL_TEST_ASSERT(inSuite, result == 'g');

    result = nl_hextobin('G');
    NL_TEST_ASSERT(inSuite, result == 'G');
}

static void TestStrHexToBin(nlTestSuite *inSuite, void *inContext)
{
    const char *hex = "0123456789ABCDEFabcdef";
    uint8_t bin[22];
    const uint8_t expected_bin[22] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
    size_t i;

    nl_strhextobin(&bin[0], &hex[0], strlen(hex));

    for (i = 0; i < 22; i++)
    {
        bin[i] = nl_hextobin(hex[i]);
        NL_TEST_ASSERT(inSuite, bin[i] == expected_bin[i]);
    }
}

static void TestBinToHexStr(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t bin1[22] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
    const char *expected_hex_wo_sep = "000102030405060708090A0B0C0D0E0F0A0B0C0D0E0F";
    const char *expected_hex_w_sep = "0001:0203:0405:0607:0809:0A0B:0C0D:0E0F:0A0B:0C0D:0E0F";
    char hex_wo_sep[45];
    char hex_w_sep[99];
    int result;

    nl_bintohexstr(&hex_wo_sep[0], &bin1[0], 22, '\0');
    result = strncmp(&hex_wo_sep[0], &expected_hex_wo_sep[0], strlen(&expected_hex_wo_sep[0]));
    NL_TEST_ASSERT(inSuite, result == 0);

    nl_bintohexstr(&hex_w_sep[0], &bin1[0], 22, ':');
    result = strncmp(&hex_w_sep[0], &expected_hex_w_sep[0], strlen(&expected_hex_w_sep[0]));
    NL_TEST_ASSERT(inSuite, result == 0);
}

static void TestIsHexStr(nlTestSuite *inSuite, void *inContext)
{
    const char *passing = "9911f7af049e8aae4971fce8ea3948806919cc49aa58cb14cbdfe6912cf08fda";
    const char *failing = "WXMsRu7dFsHCxO2hxQDNOsfxK8C8hsmvpCk3J5WNo/UI6m1dcEe5LbWPlqbzPGeZe3fvUxPNMsCz";
    bool result;

    result = nl_isxdigitstr(passing);
    NL_TEST_ASSERT(inSuite, result == true);

    result = nl_isxdigitstr(failing);
    NL_TEST_ASSERT(inSuite, result == false);

    result = nl_isxdigitstr(NULL);
    NL_TEST_ASSERT(inSuite, result == false);
}

static void TestMemoryDump(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t bytes[] = { 0x57, 0xcb, 0xe0, 0x42,
                              0xf7, 0x05, 0x2d, 0xd0,
                              0x47, 0xb5, 0x4e, 0xdd,
                              0x08, 0x9f, 0xcf, 0x29,
                              0xe8, 0x1d, 0x83, 0x15,
                              0xfa, 0x98, 0x34, 0x7f,
                              0xb5, 0x35, 0xd4, 0x33,
                              0xee, 0x2c, 0x7c, 0x24,
                              0x40, 0x3f, 0xa1, 0x98,
                              0x55, 0x5a, 0xfd, 0xf7,
                              0x6b, 0x1c, 0xf5, 0x38,
                              0x30, 0xff, 0xa4, 0x25,
                              0x20, 0x50, 0xec, 0x8f,
                              0x6a, 0x18, 0xe0, 0x9c,
                              0xc2, 0x2e, 0x96, 0x61,
                              0x57, 0xf5, 0xed, 0xec };

    nl_dump_bytes((uintptr_t)&bytes[0], &bytes[0], sizeof (bytes) / sizeof(bytes[0]));
}

static void TestStrnCpyPrettyPrint(nlTestSuite *inSuite, void *inContext)
{
    char input1[17] = { 0x62, 0x1a, 0x48, 0xea, 0x1c, 0x9a, 0xe8, 0x78, 0xa6, 0x43, 0x5a, 0x2f, 0x38, 0x66, 0x57, 0x4e, 0x00 };
    const char expected1[17] = "b.H....x.CZ/8fWN";
    char input2[17] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', ',', '+', 'D', '*', '/', 0x00 };
    const char expected2[17] = "0123456789A,+D*-";
    char input3[17] = { 'Z', 'Y', 'X', 'W', 'V', 0x00, 'T', 'S', 'R', 'Q', 'P', 'O', 'N', 'M', 'L', 'K', 0x00 };
    const char expected3[17] = "ZYXWV";
    const char input4[1] = { 0x00 };
    char output[17];
    size_t result;

    result = nl_strncpyprettyprint(NULL, input1, sizeof(output) / sizeof(output[0]));
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nl_strncpyprettyprint(output, NULL, 0);
    NL_TEST_ASSERT(inSuite, result == 0);

    result = nl_strncpyprettyprint(output, input1, sizeof(output) / sizeof(output[0]));
    NL_TEST_ASSERT(inSuite, result == strlen(expected1) + 1);
    result = strncmp(output, expected1, strlen(expected1));

    result = nl_strncpyprettyprint(output, input2, sizeof(output) / sizeof(output[0]));
    NL_TEST_ASSERT(inSuite, result == strlen(expected2) + 1);
    result = strncmp(output, expected2, strlen(expected2));

    result = nl_strncpyprettyprint(output, input3, sizeof(output) / sizeof(output[0]));
    NL_TEST_ASSERT(inSuite, result == strlen(expected3) + 1);
    result = strncmp(output, expected3, strlen(expected3));

    result = nl_strncpyprettyprint(output, input4, 0);
    NL_TEST_ASSERT(inSuite, result == 0);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("parsing delimited byte strings",             TestGetCharSeparatedBytes),
    NL_TEST_DEF("printing delimited byte strings",            TestPrintBytesWithSeparator),
    NL_TEST_DEF("character hexadecimal to binary conversion", TestHexToBin),
    NL_TEST_DEF("string hexadecimal to binary conversion",    TestStrHexToBin),
    NL_TEST_DEF("binary to hexadecimal string conversion",    TestBinToHexStr),
    NL_TEST_DEF("hexadecimal string introspection",           TestIsHexStr),
    NL_TEST_DEF("memory dump",                                TestMemoryDump),
    NL_TEST_DEF("pretty printing string copy",                TestStrnCpyPrettyPrint),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlutilities-miscellaneous",
        &sTests[0]
    };

    nl_test_set_output_style(OUTPUT_CSV);

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
