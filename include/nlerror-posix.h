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
 *      This file defines POSIX errors within the namespace of Nest
 *      Labs error encodings.
 *
 */

#ifndef NLUTILITIES_NLERROR_POSIX_H
#define NLUTILITIES_NLERROR_POSIX_H

#include <errno.h>

#include <nlerror-base.h>
#include <nlerror-components.h>

/*
 * By definition, all standard POSIX error codes should be toll-free
 * bridged and should pass the following tests:
 *
 *           -error == nlErrorPOSIX(error)
 *           -error == nlERROR(error)
 *   nlERROR(error) == nlErrorPOSIX(error)
 */

#if nlErrorComponentSystem != 0
#error "The value for the POSIX error component MUST be zero (0)!"
#endif

#define nlErrorComponentPOSIX       nlErrorComponentSystem
#define nlErrorSubComponentPOSIX    0

#define nlErrorPOSIX(e)             nlErrorEncode(nlErrorComponentPOSIX,    \
                                                  nlErrorSubComponentPOSIX, \
                                                  (e))

#define nlErrorIsPOSIX(e)           nlErrorIs(nlErrorComponentPOSIX,    \
                                              nlErrorSubComponentPOSIX, \
                                              (e))

#endif /* NLUTILITIES_NLERROR_POSIX_H */
