/*
 *
 *    Copyright (c) 2012-2018 Nest Labs, Inc.
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
 *      This file implements block- and streaming-based interfaces for
 *      base64 encoding and decoding.
 *
 */

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include <nlbase64.h>

#include <assert.h>
#include <stdint.h>

static char nl_base64_val_to_char(uint8_t val)
{
    if (val < 26)
        return 'A' + val;
    val -= 26;
    if (val < 26)
        return 'a' + val;
    val -= 26;
    if (val < 10)
        return '0' + val;
    if (val == 10)
        return '+';
    if (val == 11)
        return '/';
    return '=';
}

static uint8_t nl_base64_char_to_val(char ch)
{
    uint8_t val = ch;
    if (val == 43)
        return 62;
    if (val == 47)
        return 63;
    // NOTE: c < 48 will fall through to return UINT8_MAX below.
    val -= 48;
    if (val < 10)
        return val + 52;
    val -= 17;
    if (val < 26)
        return val;
    val -= 32;
    if (val < 26)
        return val + 26;
    return UINT8_MAX;
}

// Encode an array of bytes to a base64 string.
//
// Returns length of generated string.
// Output DOES NOT include null terminator.
// Output buffer must be at least (inLen + 3) * 4 / 3 bytes long.
// Input and output buffers CANNOT overlap.
//
uint16_t nl_base64_encode(const uint8_t *in, uint16_t inLen, char *out)
{
    char *outStart = out;

    while (inLen > 0)
    {
        uint8_t val1, val2, val3, val4;

        val1 = *in >> 2;
        val2 = (*in << 4) & 0x3F;
        in++;
        inLen--;
        if (inLen > 0)
        {
            val2 |= *in >> 4;
            val3 =  (*in << 2) & 0x3F;
            in++;
            inLen--;
            if (inLen > 0)
            {
                val3 |= *in >> 6;
                val4  = *in & 0x3F;
                in++;
                inLen--;
            }
            else
                val4 = UINT8_MAX;
        }
        else
            val3 = val4 = UINT8_MAX;

        *out++ = nl_base64_val_to_char(val1);
        *out++ = nl_base64_val_to_char(val2);
        *out++ = nl_base64_val_to_char(val3);
        *out++ = nl_base64_val_to_char(val4);
    }

    return out - outStart;
}

// Decode a base64 string to byte.
//
// Supports decode in place by setting out pointer equal to in.  UINT16_MAX returned on err.
//
uint16_t nl_base64_decode(const char *in, uint16_t inLen, uint8_t *out)
{
    uint8_t *outStart = out;

    while (inLen > 0)
    {
        if (inLen == 1)
            return UINT16_MAX;

        uint8_t a = nl_base64_char_to_val(*in++);
        uint8_t b = nl_base64_char_to_val(*in++);
        inLen -= 2;

        if (a == UINT8_MAX || b == UINT8_MAX)
            return UINT16_MAX;

        *out++ = (a << 2) | (b >> 4);

        if (inLen == 0 || *in == '=')
            break;

        uint8_t c = nl_base64_char_to_val(*in++);
        inLen--;

        if (c == UINT8_MAX)
            return UINT16_MAX;

        *out++ = (b << 4) | (c >> 2);

        if (inLen == 0 || *in == '=')
            break;

        uint8_t d = nl_base64_char_to_val(*in++);
        inLen--;

        if (d == UINT8_MAX)
            return UINT16_MAX;

        *out++ = (c << 6) | d;
    }

    return out - outStart;
}

//
// Encode Base64 in O(1) space
//
void nl_base64_stream_enc_start(nl_base64_stream_enc_state_t *state, nl_base64_stream_enc_putchar_t out_putchar, void *context)
{
    state->num_encoded = 0;
    state->num_written = 0;
    state->putchar     = out_putchar;
    state->context     = context;
}

uint16_t nl_base64_stream_enc_more(const uint8_t *in, uint16_t inLen,
                                   nl_base64_stream_enc_state_t *state)
{
    const uint16_t was_written = state->num_written;

    while (inLen > 0)
    {
        switch (state->num_encoded)
        {
        case 0:
            state->encoded[0] = *in >> 2;
            state->encoded[1] = (*in << 4) & 0x3F;
            state->num_encoded++;
            break;
        case 1:
            state->encoded[1] |= *in >> 4;
            state->encoded[2] =  (*in << 2) & 0x3F;
            state->num_encoded++;
            break;
        case 2:
            state->encoded[2] |= *in >> 6;
            state->putchar(nl_base64_val_to_char(state->encoded[0]), state->context);
            state->putchar(nl_base64_val_to_char(state->encoded[1]), state->context);
            state->putchar(nl_base64_val_to_char(state->encoded[2]), state->context);
            state->putchar(nl_base64_val_to_char(*in & 0x3F), state->context);
            state->num_encoded = 0;
            state->num_written += 4;
            break;
        default:
            assert(state->num_encoded <= 2); // Not possible
            break;
        }
        in++;
        inLen--;
    }

    return (state->num_written - was_written);
}

uint16_t nl_base64_stream_enc_finish(bool pad, nl_base64_stream_enc_state_t *state)
{
    switch (state->num_encoded)
    {
    case 0:
    default:
        break;
    case 1:
        state->putchar(nl_base64_val_to_char(state->encoded[0]), state->context);
        state->putchar(nl_base64_val_to_char(state->encoded[1]), state->context);
        state->num_written += 2;
        if (pad)
        {
            state->putchar('=', state->context);
            state->putchar('=', state->context);
            state->num_written += 2;
        }
        break;
    case 2:
        state->putchar(nl_base64_val_to_char(state->encoded[0]), state->context);
        state->putchar(nl_base64_val_to_char(state->encoded[1]), state->context);
        state->putchar(nl_base64_val_to_char(state->encoded[2]), state->context);
        state->num_written += 3;
        if (pad)
        {
            state->putchar('=', state->context);
            state->num_written += 1;
        }
        break;
    }

    return state->num_written;
}
