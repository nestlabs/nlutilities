/*
 *
 *    Copyright (c) 2014-2018 Nest Labs, Inc.
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
 *      This file defines block- and streaming-based interfaces for
 *      base64 encoding and decoding.
 *
 */

#ifndef NLUTILITIES_NLBASE64_H
#define NLUTILITIES_NLBASE64_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <nlmacros.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint16_t nl_base64_decode(const char *in, uint16_t inLen, uint8_t *out);
extern uint16_t nl_base64_encode(const uint8_t *in, uint16_t inLen, char *out);

/* Streaming Base64 encoder. Requires only 4 bytes on the stack rather
 * than an O(N) output buffer.
 */

typedef void (*nl_base64_stream_enc_putchar_t)(const uint8_t inByte, void *inContext);

typedef struct {
    uint8_t                        encoded[3];
    uint8_t                        num_encoded;
    uint16_t                       num_written;
    nl_base64_stream_enc_putchar_t putchar;
    void *                         context;
} nl_base64_stream_enc_state_t;

extern void     nl_base64_stream_enc_start(nl_base64_stream_enc_state_t *state,
                                           nl_base64_stream_enc_putchar_t out_putchar,
                                           void *context);
extern uint16_t nl_base64_stream_enc_more(const uint8_t *in, uint16_t inLen,
                                          nl_base64_stream_enc_state_t *state);
extern uint16_t nl_base64_stream_enc_finish(bool pad,
                                            nl_base64_stream_enc_state_t *state);

#ifdef __cplusplus
}
#endif

#endif // NLUTILITIES_NLBASE64_H
