/* Copyright (c) 2006-2021 Arm Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* mbed OS boot sequence
 *
 * Most of mbed supported targets use default ARM Cortex M boot approach, where the core starts executing reset vector
 * after power up. Reset ISR is defined for each target by the vendor (basing on CMSIS template). Reset vector is
 * responsible for low level platform init and then calling in libc (__main). Depending on compiler and version of C
 * library, predefined function will be called which is implemented by mbed OS.
 *
 * There's number of functions, vendor and users can provide to setup the platform and/or inject a code to be executed
 *  before main():
 *      * Reset vector and SystemInit: Reset vector should do low level core and board initialization.
 *      * mbed_sdk_init: Higher level board init and making sure the board is ready for the mbed OS.
 *      * mbed_main: User's code to be executed before main().
 *      * main: Standard application code.
 *
 * Other notes:
 *
 *    * In addition to the above, libc will use functions defined in mbed_boot.c: __rtos_malloc_lock/unlock,
 *      __rtos_env_lock/unlock.
 *
 *    * First step after the execution is passed to mbed, software_init_hook for GCC and __rt_entry for ARMC is to
 *      initialize heap.
 *
 * Memory layout notes:
 * ====================
 *
 * IAR Memory layout :
 * - Heap defined by "HEAP" region in .icf file
 * - Interrupt stack defined by "CSTACK" region in .icf file
 * - Value INITIAL_SP is ignored
 *
 * GCC Memory layout :
 * - Heap explicitly placed in linker script (*.ld file) and heap start (__end___) and heap end (__HeapLimit) should be defined in linker script
 * - Interrupt stack placed in linker script **.ld file) and stack start (__StackTop) and stack end (__StackLimit) should be defined in linker script
 *
 * ARM Memory layout :
 * - Heap can be explicitly placed by adding ARM_LIB_HEAP section in scatter file and defining both HEAP_START and HEAP_SIZE
 * - Interrupt stack placed in scatter files (*.sct) by adding ARM_LIB_STACK section
 *
 */

//#include "hal/us_ticker_api.h"
//#include "mbed_toolchain.h"
#include <stdlib.h>
#include <stdint.h>
#include "mbed_boot.h"
#include "cmsis.h"
#include "mbed_error.h"
#include "mbed_mpu_mgmt.h"
#include "mbed_assert.h"

/* This startup is for baremetal. There is no RTOS in baremetal,
 * therefore we protect this file with MBED_CONF_RTOS_PRESENT.
 * Note: The start-up code for mbed OS is in cmsis/device/rtos/TOOLCHAIN_<TOOLCHAIN>/mbed_boot_<TOOLCHAIN>.c code file.
 */

/* Heap limits - only used if set */
//extern unsigned char *mbed_heap_start;
//extern uint32_t mbed_heap_size;

unsigned char *mbed_heap_start = 0;
uint32_t mbed_heap_size = 0;

/* Stack limits */
unsigned char *mbed_stack_isr_start = 0;
uint32_t mbed_stack_isr_size = 0;


/* mbed_main is a function that is called before main()
 * mbed_sdk_init() is also a function that is called before main(), but unlike
 * mbed_main(), it is not meant for user code, but for the SDK itself to perform
 * initializations before main() is called.
 */
MBED_WEAK void mbed_main(void)
{

}

/* This function can be implemented by the target to perform higher level target initialization
 */
MBED_WEAK void mbed_sdk_init(void)
{
    // Nothing by default
}

MBED_WEAK void software_init_hook_rtos()
{
    // Nothing by default
}

static void mbed_cpy_nvic(void)
{
    /* If vector address in RAM is defined, copy and switch to dynamic vectors. Exceptions for M0 which doesn't have
    VTOR register and for A9 for which CMSIS doesn't define NVIC_SetVector; in both cases target code is
    responsible for correctly handling the vectors.
    */
#if !defined(__CORTEX_M0) && !defined(__CORTEX_A9)
#ifdef NVIC_RAM_VECTOR_ADDRESS
    uint32_t *old_vectors = (uint32_t *)SCB->VTOR;
    uint32_t *vectors = (uint32_t *)NVIC_RAM_VECTOR_ADDRESS;
    for (int i = 0; i < NVIC_NUM_VECTORS; i++) {
        vectors[i] = old_vectors[i];
    }
    SCB->VTOR = (uint32_t)NVIC_RAM_VECTOR_ADDRESS;
#endif /* NVIC_RAM_VECTOR_ADDRESS */
#endif /* !defined(__CORTEX_M0) && !defined(__CORTEX_A9) */
}


void mbed_init(void)
{
    // Configs to make debugging easier
#ifdef SCnSCB_ACTLR_DISDEFWBUF_Msk
    // Disable write buffer to make BusFaults (eg write to ROM via NULL pointer) precise.
    // Possible on Cortex-M3 and M4, not on M0, M7 or M33.
    // Would be less necessary if ROM was write-protected in MPU to give a
    // precise MemManage exception.
    SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;
#endif
    mbed_cpy_nvic(); // Copy NVIC to RAM
    mbed_sdk_init(); // Vendor specific init
#if DEVICE_MPU && MBED_CONF_PLATFORM_USE_MPU
    mbed_mpu_manager_init();
#endif
}

#if defined (__ARMCC_VERSION)

extern uint32_t               Image$$ARM_LIB_STACK$$ZI$$Base[];
extern uint32_t               Image$$ARM_LIB_STACK$$ZI$$Length[];
extern uint32_t               Image$$ARM_LIB_HEAP$$ZI$$Base[];
extern uint32_t               Image$$ARM_LIB_HEAP$$ZI$$Length[];

// The original unpacthed main() function that gets called from __main().
// It refers to the user application's main.
int $Super$$main(void);

/**
  * @details Patches the definition of the original main() function called from the C
  * run time library so this one is called instead of the original main()
  * unpatched main() function.
  */
int $Sub$$main(void)
{
    // Record the base addresses and sizes of the stack and heap as defined
    // in the scatter file.
    mbed_stack_isr_start = (unsigned char *) Image$$ARM_LIB_STACK$$ZI$$Base;
    mbed_stack_isr_size = (uint32_t) Image$$ARM_LIB_STACK$$ZI$$Length;
    mbed_heap_start = (unsigned char *) Image$$ARM_LIB_HEAP$$ZI$$Base;
    mbed_heap_size = (uint32_t) Image$$ARM_LIB_HEAP$$ZI$$Length;

    mbed_init();
    mbed_main();
    return $Super$$main();
}

#if defined(__MICROLIB)
MBED_WEAK void __aeabi_assert(const char *expr, const char *file, int line)
{
    mbed_assert_internal(expr, file, line);
}
#endif // defined(__MICROLIB)

#elif defined (__GNUC__)

extern uint32_t             __StackLimit;
extern uint32_t             __StackTop;
extern uint32_t             __end__;
extern uint32_t             __HeapLimit;

extern int __real_main(void);

/**
  * @details A strongly-linked definition of GCC's software_init_hook() function so
  * it is called at startup prior to main().
  */
void software_init_hook(void)
{
    // Record the base addresses and sizes of the stack and heap as defined
    // in the linker file.
    mbed_stack_isr_start = (unsigned char *) &__StackLimit;
    mbed_stack_isr_size = (uint32_t) &__StackTop - (uint32_t) &__StackLimit;
    mbed_heap_start = (unsigned char *) &__end__;
    mbed_heap_size = (uint32_t) &__HeapLimit - (uint32_t) &__end__;

    mbed_init();
    software_init_hook_rtos();
}

/**
 * @details Ensures main() called from the C run time library is linked to __wrap_main().
 * __real_main() refers to the user application's main().
 */
int __wrap_main(void)
{
    mbed_main();
    //mbed_error_initialize();
    return __real_main();
}

/**
 * @brief Retarget of exit for GCC.
 * @details Unlike the standard version, this function doesn't call any function
 * registered with atexit before calling _exit.
 */
void __wrap_exit(int return_code)
{
    _exit(return_code);
}

/**
 * @brief Retarget atexit from GCC.
 * @details This function will always fail and never register any handler to be
 * called at exit.
 */
int __wrap_atexit(void (*func)())
{
    return 1;
}

#endif
