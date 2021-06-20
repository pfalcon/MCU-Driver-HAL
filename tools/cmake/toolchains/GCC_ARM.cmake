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

set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(GCC_ELF2BIN "arm-none-eabi-objcopy")
set_property(GLOBAL PROPERTY ELF2BIN ${GCC_ELF2BIN})

# build toolchain flags that get passed to everything (including CMake compiler checks)
list(APPEND link_options
    "-Wl,--start-group"
        "-lstdc++"
        "-lsupc++"
        "-lm"
        "-lc"
        "-lgcc"
        "-lnosys"
    "-Wl,--end-group"
    "-specs=nosys.specs"
    "-Wl,--cref"
)

# Add linking time preprocessor macro for TFM targets
if("TFM" IN_LIST MBED_TARGET_LABELS)
    list(APPEND link_options
        "-DDOMAIN_NS=1"
    )
endif()

list(APPEND common_options
    "-Wall"
    "-Wextra"
    "-Wno-unused-parameter"
    "-Wno-missing-field-initializers"
    "-fmessage-length=0"
    "-fno-exceptions"
    "-ffunction-sections"
    "-fdata-sections"
    "-funsigned-char"
    "-fomit-frame-pointer"
    "-g3"
)


# Configure the toolchain to select the selected C library
function(mbed_set_c_lib target lib_type)
    if (${lib_type} STREQUAL "small")
        target_compile_definitions(${target}
            INTERFACE
                MBED_RTOS_SINGLE_THREAD
                __NEWLIB_NANO
        )

        target_link_options(${target}
            INTERFACE
                "--specs=nano.specs"
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

        set(printf_link_options "")
        list(APPEND printf_link_options
            "-Wl,--wrap,printf"
            "-Wl,--wrap,sprintf"
            "-Wl,--wrap,snprintf"
            "-Wl,--wrap,vprintf"
            "-Wl,--wrap,vsprintf"
            "-Wl,--wrap,vsnprintf"
            "-Wl,--wrap,fprintf"
            "-Wl,--wrap,vfprintf"
        )
        target_link_options(${target}
            INTERFACE
                ${printf_link_options}
        )
    endif()
endfunction()

# Add linker flags to generate a mapfile with a given name
function(mbed_configure_memory_map target mapfile)
    target_link_options(${target}
        PRIVATE
            "-Wl,-Map=${mapfile}"
    )
endfunction()
