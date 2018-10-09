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
#      This file is the GNU automake template for the Nest Labs Utilities
#      unit tests.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

#
# Local headers to build against and distribute but not to install
# since they are not part of the package.
#
noinst_HEADERS                                 = \
    $(NULL)

#
# Other files we do want to distribute with the package.
#
EXTRA_DIST                                     = \
    $(NULL)

if NLUTILITIES_BUILD_TESTS
# C preprocessor option flags that will apply to all compiled objects in this
# makefile.

AM_CPPFLAGS                                    = \
    -I$(top_srcdir)/include                      \
    $(NULL)

COMMON_LDADD                                   = \
    -L${top_builddir}/src -lnlutilities
    $(NULL)

# Test applications that should be run when the 'check' target is run.

check_PROGRAMS                                 = \
    nlutilities-test-abs                         \
    nlutilities-test-algorithm-cxx               \
    nlutilities-test-alignment                   \
    nlutilities-test-base64                      \
    nlutilities-test-binhex                      \
    nlutilities-test-error                       \
    nlutilities-test-fixedpoint                  \
    nlutilities-test-macros                      \
    nlutilities-test-memset16                    \
    nlutilities-test-miscellaneous               \
    nlutilities-test-new-cxx                     \
    nlutilities-test-noncopyable-cxx             \
    $(NULL)

# Test applications and scripts that should be built and run when the
# 'check' target is run.

TESTS                                          = \
    $(check_PROGRAMS)                            \
    $(NULL)

# The additional environment variables and their values that will be
# made available to all programs and scripts in TESTS.

TESTS_ENVIRONMENT                              = \
    $(NULL)

# Source, compiler, and linker options for test programs.

nlutilities_test_abs_SOURCES                   = nlutilities-test-algorithm-cxx.cpp
nlutilities_test_abs_LDADD                     = $(COMMON_LDADD)

nlutilities_test_algorithm_cxx_SOURCES         = nlutilities-test-algorithm-cxx.cpp
nlutilities_test_algorithm_cxx_LDADD           = $(COMMON_LDADD)

nlutilities_test_alignment_SOURCES             = nlutilities-test-alignment.c
nlutilities_test_alignment_LDADD               = $(COMMON_LDADD)

nlutilities_test_base64_SOURCES                = nlutilities-test-base64.c
nlutilities_test_base64_LDADD                  = $(COMMON_LDADD)

nlutilities_test_binhex_SOURCES                = nlutilities-test-binhex.c
nlutilities_test_binhex_LDADD                  = $(COMMON_LDADD)

nlutilities_test_error_SOURCES                 = nlutilities-test-error.c
nlutilities_test_error_LDADD                   = $(COMMON_LDADD)

nlutilities_test_fixedpoint_SOURCES            = nlutilities-test-fixedpoint.c
nlutilities_test_fixedpoint_LDADD              = $(COMMON_LDADD)

nlutilities_test_macros_SOURCES                = nlutilities-test-macros.c
nlutilities_test_macros_LDADD                  = $(COMMON_LDADD)

nlutilities_test_memset16_SOURCES              = nlutilities-test-memset16.c
nlutilities_test_memset16_LDADD                = $(COMMON_LDADD)

nlutilities_test_miscellaneous_SOURCES         = nlutilities-test-miscellaneous.c
nlutilities_test_miscellaneous_LDADD           = $(COMMON_LDADD)

nlutilities_test_new_cxx_SOURCES               = nlutilities-test-new-cxx.cpp
nlutilities_test_new_cxx_LDADD                 = $(COMMON_LDADD)

nlutilities_test_noncopyable_cxx_SOURCES       = nlutilities-test-noncopyable-cxx.cpp
nlutilities_test_noncopyable_cxx_LDADD         = $(COMMON_LDADD)

if NLUTILITIES_BUILD_COVERAGE
CLEANFILES                                     = $(wildcard *.gcda *.gcno)

if NLUTILITIES_BUILD_COVERAGE_REPORTS
# The bundle should positively be qualified with the absolute build
# path. Otherwise, VPATH will get auto-prefixed to it if there is
# already such a directory in the non-colocated source tree.

NLUTILITIES_COVERAGE_BUNDLE                           = ${abs_builddir}/${PACKAGE}${NL_COVERAGE_BUNDLE_SUFFIX}
NLUTILITIES_COVERAGE_INFO                             = ${NLUTILITIES_COVERAGE_BUNDLE}/${PACKAGE}${NL_COVERAGE_INFO_SUFFIX}

$(NLUTILITIES_COVERAGE_BUNDLE):
	$(call create-directory)

$(NLUTILITIES_COVERAGE_INFO): check | $(NLUTILITIES_COVERAGE_BUNDLE)
	$(call generate-coverage-report,${top_builddir})

coverage: $(NLUTILITIES_COVERAGE_INFO)

clean-local: clean-local-coverage

.PHONY: clean-local-coverage
clean-local-coverage:
	-$(AM_V_at)rm -rf $(NLUTILITIES_COVERAGE_BUNDLE)
endif # NLUTILITIES_BUILD_COVERAGE_REPORTS
endif # NLUTILITIES_BUILD_COVERAGE
endif # NLUTILITIES_BUILD_TESTS

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
