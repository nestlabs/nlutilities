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

#include <math.h>
#include <stdint.h>

#include <nlfixedpoint.h>

#include <nlunit-test.h>

static void TestTypeWidth(nlTestSuite *inSuite, void *inContext)
{
    size_t  result;

    result = sizeof (qint_t);
    NL_TEST_ASSERT(inSuite, result == 4);

    result = sizeof (quint_t);
    NL_TEST_ASSERT(inSuite, result == 4);
}

static void TestQDeclarations(nlTestSuite *inSuite, void *inContext)
{
    qint_t qs;
    quint_t qu;

    // Signed

    // (1) with all declarations up through wraparound

    qs = Qs1(1);
    NL_TEST_ASSERT(inSuite, qs == 2);

    qs = Qs2(1);
    NL_TEST_ASSERT(inSuite, qs == 4);

    qs = Qs3(1);
    NL_TEST_ASSERT(inSuite, qs == 8);

    qs = Qs4(1);
    NL_TEST_ASSERT(inSuite, qs == 16);

    qs = Qs5(1);
    NL_TEST_ASSERT(inSuite, qs == 32);

    qs = Qs6(1);
    NL_TEST_ASSERT(inSuite, qs == 64);

    qs = Qs7(1);
    NL_TEST_ASSERT(inSuite, qs == 128);

    qs = Qs8(1);
    NL_TEST_ASSERT(inSuite, qs == 256);

    qs = Qs9(1);
    NL_TEST_ASSERT(inSuite, qs == 512);

    qs = Qs10(1);
    NL_TEST_ASSERT(inSuite, qs == 1024);

    qs = Qs11(1);
    NL_TEST_ASSERT(inSuite, qs == 2048);

    qs = Qs12(1);
    NL_TEST_ASSERT(inSuite, qs == 4096);

    qs = Qs13(1);
    NL_TEST_ASSERT(inSuite, qs == 8192);

    qs = Qs14(1);
    NL_TEST_ASSERT(inSuite, qs == 16384);

    qs = Qs15(1);
    NL_TEST_ASSERT(inSuite, qs == 32768);

    qs = Qs16(1);
    NL_TEST_ASSERT(inSuite, qs == 65536);

    qs = Qs17(1);
    NL_TEST_ASSERT(inSuite, qs == 131072);

    qs = Qs18(1);
    NL_TEST_ASSERT(inSuite, qs == 262144);

    qs = Qs19(1);
    NL_TEST_ASSERT(inSuite, qs == 524288);

    qs = Qs20(1);
    NL_TEST_ASSERT(inSuite, qs == 1048576);

    qs = Qs21(1);
    NL_TEST_ASSERT(inSuite, qs == 2097152);

    qs = Qs22(1);
    NL_TEST_ASSERT(inSuite, qs == 4194304);

    qs = Qs23(1);
    NL_TEST_ASSERT(inSuite, qs == 8388608);

    qs = Qs24(1);
    NL_TEST_ASSERT(inSuite, qs == 16777216);

    qs = Qs25(1);
    NL_TEST_ASSERT(inSuite, qs == 33554432);

    qs = Qs26(1);
    NL_TEST_ASSERT(inSuite, qs == 67108864);

    qs = Qs27(1);
    NL_TEST_ASSERT(inSuite, qs == 134217728);

    qs = Qs28(1);
    NL_TEST_ASSERT(inSuite, qs == 268435456);

    qs = Qs29(1);
    NL_TEST_ASSERT(inSuite, qs == 536870912);

    qs = Qs30(1);
    NL_TEST_ASSERT(inSuite, qs == 1073741824);

    // (-1) with all declarations

    qs = Qs1(-1);
    NL_TEST_ASSERT(inSuite, qs == -2);

    qs = Qs3(-1);
    NL_TEST_ASSERT(inSuite, qs == -8);

    qs = Qs5(-1);
    NL_TEST_ASSERT(inSuite, qs == -32);

    qs = Qs7(-1);
    NL_TEST_ASSERT(inSuite, qs == -128);

    qs = Qs11(-1);
    NL_TEST_ASSERT(inSuite, qs == -2048);

    qs = Qs13(-1);
    NL_TEST_ASSERT(inSuite, qs == -8192);

    qs = Qs17(-1);
    NL_TEST_ASSERT(inSuite, qs == -131072);

    qs = Qs19(-1);
    NL_TEST_ASSERT(inSuite, qs == -524288);

    qs = Qs23(-1);
    NL_TEST_ASSERT(inSuite, qs == -8388608);

    qs = Qs29(-1);
    NL_TEST_ASSERT(inSuite, qs == -536870912);

    // Pi with prime declarations

    qs = Qs1(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 6);

    qs = Qs3(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 25);

    qs = Qs5(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 100);

    qs = Qs7(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 402);

    qs = Qs11(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 6433);

    qs = Qs13(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 25735);

    qs = Qs17(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 411774);

    qs = Qs19(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 1647099);

    qs = Qs23(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 26353589);

    qs = Qs29(M_PI);
    NL_TEST_ASSERT(inSuite, qs == 1686629713);

    // Unsigned

    // (1) with all declarations

    qu = Qu1(1);
    NL_TEST_ASSERT(inSuite, qu == 2);

    qu = Qu2(1);
    NL_TEST_ASSERT(inSuite, qu == 4);

    qu = Qu3(1);
    NL_TEST_ASSERT(inSuite, qu == 8);

    qu = Qu4(1);
    NL_TEST_ASSERT(inSuite, qu == 16);

    qu = Qu5(1);
    NL_TEST_ASSERT(inSuite, qu == 32);

    qu = Qu6(1);
    NL_TEST_ASSERT(inSuite, qu == 64);

    qu = Qu7(1);
    NL_TEST_ASSERT(inSuite, qu == 128);

    qu = Qu8(1);
    NL_TEST_ASSERT(inSuite, qu == 256);

    qu = Qu9(1);
    NL_TEST_ASSERT(inSuite, qu == 512);

    qu = Qu10(1);
    NL_TEST_ASSERT(inSuite, qu == 1024);

    qu = Qu11(1);
    NL_TEST_ASSERT(inSuite, qu == 2048);

    qu = Qu12(1);
    NL_TEST_ASSERT(inSuite, qu == 4096);

    qu = Qu13(1);
    NL_TEST_ASSERT(inSuite, qu == 8192);

    qu = Qu14(1);
    NL_TEST_ASSERT(inSuite, qu == 16384);

    qu = Qu15(1);
    NL_TEST_ASSERT(inSuite, qu == 32768);

    qu = Qu16(1);
    NL_TEST_ASSERT(inSuite, qu == 65536);

    qu = Qu17(1);
    NL_TEST_ASSERT(inSuite, qu == 131072);

    qu = Qu18(1);
    NL_TEST_ASSERT(inSuite, qu == 262144);

    qu = Qu19(1);
    NL_TEST_ASSERT(inSuite, qu == 524288);

    qu = Qu20(1);
    NL_TEST_ASSERT(inSuite, qu == 1048576);

    qu = Qu21(1);
    NL_TEST_ASSERT(inSuite, qu == 2097152);

    qu = Qu22(1);
    NL_TEST_ASSERT(inSuite, qu == 4194304);

    qu = Qu23(1);
    NL_TEST_ASSERT(inSuite, qu == 8388608);

    qu = Qu24(1);
    NL_TEST_ASSERT(inSuite, qu == 16777216);

    qu = Qu25(1);
    NL_TEST_ASSERT(inSuite, qu == 33554432);

    qu = Qu26(1);
    NL_TEST_ASSERT(inSuite, qu == 67108864);

    qu = Qu27(1);
    NL_TEST_ASSERT(inSuite, qu == 134217728);

    qu = Qu28(1);
    NL_TEST_ASSERT(inSuite, qu == 268435456);

    qu = Qu29(1);
    NL_TEST_ASSERT(inSuite, qu == 536870912);

    qu = Qu30(1);
    NL_TEST_ASSERT(inSuite, qu == 1073741824);

    qu = Qu31(1);
    NL_TEST_ASSERT(inSuite, qu == 2147483648);

    // Pi with prime declarations

    qu = Qu1(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 6);

    qu = Qu3(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 25);

    qu = Qu5(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 100);

    qu = Qu7(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 402);

    qu = Qu11(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 6433);

    qu = Qu13(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 25735);

    qu = Qu17(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 411774);

    qu = Qu19(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 1647099);

    qu = Qu23(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 26353589);

    qu = Qu29(M_PI);
    NL_TEST_ASSERT(inSuite, qu == 1686629713);
}

static void TestQConversions(nlTestSuite *inSuite, void *inContext)
{
    qint_t qs;
    quint_t qu;

    // Down Conversions

    // Scalar Down Conversions

    // Signed

    qs = Qdown(29, 23, Qs29(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -26353589);

    qs = Qdown(23, 19, Qs23(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -1647099);

    qs = Qdown(19, 17, Qs19(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -411774);

    qs = Qdown(17, 13, Qs17(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -25735);

    qs = Qdown(13, 11, Qs13(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -6433);

    qs = Qdown(11, 7, Qs11(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = 402);

    qs = Qdown(7, 5, Qs7(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -100);

    qs = Qdown(5, 3, Qs5(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -25);

    qs = Qdown(3, 1, Qs3(-M_PI));
    NL_TEST_ASSERT(inSuite, qs = -6);

    // Unsigned

    qu = Qdown(29, 23, Qu29(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 26353589);

    qu = Qdown(23, 19, Qu23(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 1647099);

    qu = Qdown(19, 17, Qu19(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 411774);

    qu = Qdown(17, 13, Qu17(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 25735);

    qu = Qdown(13, 11, Qu13(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 6433);

    qu = Qdown(11, 7, Qu11(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 402);

    qu = Qdown(7, 5, Qu7(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 100);

    qu = Qdown(5, 3, Qu5(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 25);

    qu = Qdown(3, 1, Qu3(M_PI));
    NL_TEST_ASSERT(inSuite, qu = 6);

    // Integer Trucation Down Conversions

    // Signed

    qs = Qint(1, Qs1(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(3, Qs3(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(5, Qs5(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(7, Qs7(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(11, Qs11(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(13, Qs13(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(17, Qs17(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(19, Qs19(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(23, Qs23(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    qs = Qint(29, Qs29(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -3);

    // Unsigned

    qu = Qint(1, Qu1(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(3, Qu3(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(5, Qu5(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(7, Qu7(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(11, Qu11(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(13, Qu13(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(17, Qu17(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(19, Qu19(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(23, Qu23(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    qu = Qint(29, Qu29(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 3);

    // Up Conversions

    // Signed

    qs = Qup(1, 3, Qs1(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -24);

    qs = Qup(3, 5, Qs3(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -100);

    qs = Qup(5, 7, Qs5(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -400);

    qs = Qup(7, 11, Qs7(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -6432);

    qs = Qup(11, 13, Qs11(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -25732);

    qs = Qup(13, 17, Qs13(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -411760);

    qs = Qup(17, 19, Qs17(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -1647096);

    qs = Qup(19, 23, Qs19(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -26353584);

    qs = Qup(23, 29, Qs23(-M_PI));
    NL_TEST_ASSERT(inSuite, qs == -1686629696);

    // Unsigned

    qu = Qup(1, 3, Qu1(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 24);

    qu = Qup(3, 5, Qu3(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 100);

    qu = Qup(5, 7, Qu5(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 400);

    qu = Qup(7, 11, Qu7(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 6432);

    qu = Qup(11, 13, Qu11(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 25732);

    qu = Qup(13, 17, Qu13(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 411760);

    qu = Qup(17, 19, Qu17(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 1647096);

    qu = Qup(19, 23, Qu19(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 26353584);

    qu = Qup(23, 29, Qu23(M_PI));
    NL_TEST_ASSERT(inSuite, qu == 1686629696);
}

static void TestIntToFixed(nlTestSuite *inSuite, void *inContext)
{
    // resolution = 0.0098 per count
    // precision  = 0.0078125 per count

    const uint32_t Qresolution = 0x141205C; // 0.0098 per bit, Q.31
    int16_t        count;
    size_t         desired_frac_bits;
    int32_t        rs32;
    uint32_t       ru32;
    int            retval;

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

    // Test Fractional Bits

    count = 1000;
    desired_frac_bits = 2;

    retval = nl_int16_to_fixed32(&rs32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0x27);

    count = 1000;
    desired_frac_bits = 3;

    retval = nl_int16_to_fixed32(&rs32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0x4E);

    count = -2000;
    desired_frac_bits = 7;

    retval = nl_int16_to_fixed32(&rs32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0xFFFFF633);

    // Test Signedness

    count = 1000;
    desired_frac_bits = 7;

    retval = nl_uint16_to_fixed32(&ru32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, ru32 == 0x4E6);

    count = 1000;
    desired_frac_bits = 7;

    retval = nl_int16_to_fixed32(&rs32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0x4E6);

    count = -4000;
    desired_frac_bits = 7;

    retval = nl_int16_to_fixed32(&rs32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0xFFFFEC66);

    count = 0;
    desired_frac_bits = 7;

    retval = nl_int16_to_fixed32(&rs32, count, Qresolution, desired_frac_bits);
    NL_TEST_ASSERT(inSuite, retval == 0);
    NL_TEST_ASSERT(inSuite, rs32 == 0);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("type width",                  TestTypeWidth),
    NL_TEST_DEF("q declarations",              TestQDeclarations),
    NL_TEST_DEF("q conversions",               TestQConversions),
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
