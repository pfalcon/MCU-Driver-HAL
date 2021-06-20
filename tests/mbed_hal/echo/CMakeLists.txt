# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set(TEST_TARGET_LIB sdfx-test-echo)

add_library(${TEST_TARGET_LIB} OBJECT)

target_sources(${TEST_TARGET_LIB}
    PRIVATE
        main.cpp
)

target_link_libraries(${TEST_TARGET_LIB}
    PRIVATE
        mbed-os
        greentea::client
        test-harness
)
