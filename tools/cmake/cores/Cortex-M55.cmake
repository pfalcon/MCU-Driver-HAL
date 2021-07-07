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

# Sets cpu core options
if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    list(APPEND common_options
        "-mthumb"
        "-mfpu=fpv5-sp-d16"
        "-mfloat-abi=softfp"
        "-mcpu=cortex-m55"
    )
elseif(${MBED_TOOLCHAIN} STREQUAL "ARM")
    list(APPEND common_options
        "-mfpu=fpv5-sp-d16"
        "-mfloat-abi=hard"
        "-mcpu=cortex-m55"
    )
endif()

# We'd like to use just "-mcpu=cortex-m55" in common_options, but due to a bug
# in armclang passing options to armasm, we use the following flags as a
# workaround to select M55.
list(APPEND asm_compile_options
    -mcpu=cortex-r7
    -Wa,--cpu=cortex-m55
)

function(mbed_set_cpu_core_definitions target)
    target_compile_definitions(${target}
        INTERFACE
            __CORTEX_M55
            __FPU_PRESENT=1U
            __CMSIS_RTOS
            __MBED_CMSIS_RTOS_CM
            __SAUREGION_PRESENT=1U
            __MPU_PRESENT=1U
            __VTOR_PRESENT=1U
            __Vendor_SysTickConfig=0U
            __FPU_DP=1U
            __MVE_PRESENT=1U
            __MVE_FP=1U
            __NVIC_PRIO_BITS=3U
            __DSP_PRESENT=1U

    )
endfunction()
