#
#    Copyright 2018 Google LLC
#    All Rights Reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the GNU automake template for the Nest Labs Utilities.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

lib_LIBRARIES                       = libnlutilities.a

libnlutilities_a_CPPFLAGS           = \
    -I$(top_srcdir)/include           \
    $(NULL)

libnlutilities_a_SOURCES            = \
    nlabs-variants.c                  \
    nlbase64.c                        \
    nlbintohex.c                      \
    nldumpbytes.c                     \
    nlfixedpoint.c                    \
    nlgetcharseparatedbytes.c         \
    nlhextobin.c                      \
    nlisxdigitstr.c                   \
    nlmemset16.c                      \
    nlstrhextobin.c                   \
    nlstrutilities.c                  \
    nluif.c                           \
    $(NULL)

if NLUTILITIES_BUILD_COVERAGE
CLEANFILES                          = $(wildcard *.gcda *.gcno)
endif # NLUTILITIES_BUILD_COVERAGE

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
