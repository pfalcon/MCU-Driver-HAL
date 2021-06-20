# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

if(NOT GREENTEA_CLIENT_STDIO)
    target_include_directories(client
        INTERFACE
            .
            include
            include/greentea-custom_io
    )

    target_sources(client
        INTERFACE
            source/greentea_custom_io.c
    )
endif()
