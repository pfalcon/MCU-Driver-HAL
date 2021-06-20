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

# Set the default build type if none is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Develop" CACHE
        STRING "The build type" FORCE
   )
endif()

set(MBED_BUILD_TYPES Debug Release Develop)

# Force the build types to be case-insensitive for checking
set(LOWERCASE_MBED_BUILD_TYPES ${MBED_BUILD_TYPES})
list(TRANSFORM LOWERCASE_MBED_BUILD_TYPES TOLOWER)
string(TOLOWER ${CMAKE_BUILD_TYPE} LOWERCASE_CMAKE_BUILD_TYPE)

# Mapping CMAKE_BUILD_TYPE into MBED_BUILD_TYPES, as we understand only 3 profiles
get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(multi_config)
    # Provide only a list as multi configuration generators do not support build type
    set(CMAKE_CONFIGURATION_TYPES "${MBED_BUILD_TYPES}" CACHE STRING "List of supported build types" FORCE)
else()
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${MBED_BUILD_TYPES}")

    if(NOT LOWERCASE_CMAKE_BUILD_TYPE IN_LIST LOWERCASE_MBED_BUILD_TYPES)
        message(FATAL_ERROR "Invalid build type '${CMAKE_BUILD_TYPE}'. Possible values:\n ${MBED_BUILD_TYPES}")
    endif()
endif()

include(profiles/${LOWERCASE_CMAKE_BUILD_TYPE})
