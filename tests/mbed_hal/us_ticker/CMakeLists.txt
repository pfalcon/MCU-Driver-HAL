# Copyright (c) 2020-2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_library(sdfx-test-us_ticker OBJECT)

target_sources(sdfx-test-us_ticker
    PRIVATE
        main.cpp
)

target_link_libraries(sdfx-test-us_ticker
    PRIVATE
        mbed-os
        greentea::client
        test-harness
)
