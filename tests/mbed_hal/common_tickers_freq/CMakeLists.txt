# Copyright (c) 2020-2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_library(sdfx-test-common_tickers_freq OBJECT)

target_sources(sdfx-test-common_tickers_freq
    PRIVATE
        main.cpp
)

target_link_libraries(sdfx-test-common_tickers_freq
    PRIVATE
        mbed-os
        greentea::client
        test-harness
)
