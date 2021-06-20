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

cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../.. CACHE INTERNAL "")
set(TEST_TARGET mbed-hal-qspi)

include(${MBED_PATH}/tools/cmake/mbed_greentea.cmake)

project(${TEST_TARGET})

if(TARGET mbed-ep-agora)
    set(FLASH_TARGET_CONFIG_HEADER NORDIC/EP_AGORA)
elseif(TARGET mbed-nrf52840-dk)
    set(FLASH_TARGET_CONFIG_HEADER NORDIC/NRF52840_DK)
elseif(TARGET mbed-k82f)
    set(FLASH_TARGET_CONFIG_HEADER NXP/K82F)
elseif(TARGET mbed-lpc546xx)
    set(FLASH_TARGET_CONFIG_HEADER NXP/LPC546XX)
elseif(TARGET mbed-efm32gg11-stk3701)
    set(FLASH_TARGET_CONFIG_HEADER SiliconLabs/EFM32GG11_STK3701)
endif()

list(APPEND TEST_HEADER_DIRS flash_configs flash_configs/${FLASH_TARGET_CONFIG_HEADER})

mbed_greentea_add_test(TEST_NAME ${TEST_TARGET}
    TEST_SOURCES qspi_test_utils.cpp
    TEST_INCLUDE_DIRS ${TEST_HEADER_DIRS}
)

