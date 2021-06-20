# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

target_include_directories(test-harness
    INTERFACE
        .
        unity
)

target_sources(test-harness
    INTERFACE
        source/unity.c
)
