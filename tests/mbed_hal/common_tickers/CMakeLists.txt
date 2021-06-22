# Copyright (c) 2020-2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_library(sdfx-test-common_tickers OBJECT)

target_sources(sdfx-test-common_tickers
    PRIVATE
        main.cpp
)

target_link_libraries(sdfx-test-common_tickers
    PRIVATE
        mbed-os
        greentea::client
        test-harness
)
