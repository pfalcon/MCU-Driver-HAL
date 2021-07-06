# Copyright (c) 2020-2021 Arm Limited
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_library(sdfx-test-trng OBJECT)

target_include_directories(sdfx-test-trng
    PRIVATE
        base64b
        pithy
)

target_sources(sdfx-test-trng
    PRIVATE
        main.cpp
        base64b/base64b.cpp
        pithy/pithy.c
)

target_link_libraries(sdfx-test-trng
    PRIVATE
        mbed-os
        greentea::client
        test-harness
)
