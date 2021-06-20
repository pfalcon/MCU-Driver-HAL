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

set(CMAKE_ASM_COMPILER "armclang")
set(CMAKE_C_COMPILER "armclang")
set(CMAKE_CXX_COMPILER "armclang")
set(CMAKE_AR "armar")
set(ARM_ELF2BIN "fromelf")
set_property(GLOBAL PROPERTY ELF2BIN ${ARM_ELF2BIN})

# tell cmake about compiler targets.
# This will cause it to add the --target flag.
set(CMAKE_C_COMPILER_TARGET arm-arm-none-eabi)
set(CMAKE_CXX_COMPILER_TARGET arm-arm-none-eabi)

# Sets toolchain options
list(APPEND common_options
    "-mthumb"
    "-Wno-armcc-pragma-push-pop"
    "-Wno-armcc-pragma-anon-unions"
    "-Wno-reserved-user-defined-literal"
    "-Wno-deprecated-register"
    "-fdata-sections"
    "-fno-exceptions"
    "-fshort-enums"
    "-fshort-wchar"
)

list(APPEND asm_compile_options
    -masm=auto
    --target=arm-arm-none-eabi
)

# Add linking time preprocessor macro for TFM targets
if(MBED_CPU_CORE MATCHES "-NS$")
    list(APPEND link_options
        "--predefine=\"-DDOMAIN_NS=0x1\""
    )
endif()

# Configure the toolchain to select the selected C library
function(mbed_set_c_lib target lib_type)
    if (${lib_type} STREQUAL "small")
        target_compile_definitions(${target}
            INTERFACE
                MBED_RTOS_SINGLE_THREAD
                __MICROLIB
        )

        target_link_options(${target}
            INTERFACE
                "--library_type=microlib"
        )
    endif()
endfunction()

# Configure the toolchain to select the selected printf library
function(mbed_set_printf_lib target lib_type)
    if (${lib_type} STREQUAL "minimal-printf")
        target_compile_definitions(${target}
            INTERFACE
                MBED_MINIMAL_PRINTF
        )
    endif()
endfunction()

# Add linker flags to generate a mapfile with a given name
# `mapfile` is overridden as CMake provides the name of the diagnostic output
# file by providing armlink with the --list command line option.
# See https://gitlab.kitware.com/cmake/cmake/-/issues/21538
function(mbed_configure_memory_map target mapfile)
    target_link_options(${target}
        PRIVATE
            "--map"
            "--list=${mapfile}"
    )
endfunction()
