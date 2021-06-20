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

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
// #include "device.h"
// #include "platform/source/mbed_crash_data_offsets.h"
// #include "platform/mbed_atomic.h"
// #include "platform/mbed_critical.h"
#include "mbed_error.h"
// #include "platform/mbed_interface.h"
// #include "platform/mbed_power_mgmt.h"
// #include "platform/mbed_stats.h"
// #include "platform/internal/mbed_fault_handler.h"
// #include "platform/internal/mbed_error_hist.h"
// #include "drivers/MbedCRC.h"
// #include "mbed_rtx.h"
#ifdef MBED_CONF_RTOS_PRESENT
//#include "rtx_os.h"
#endif

#if DEVICE_STDIO_MESSAGES
#include <stdio.h>
#endif
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef NDEBUG
#define ERROR_REPORT(ctx, error_msg, error_filename, error_line) print_error_report(ctx, error_msg, error_filename, error_line)
//static void print_error_report(const mbed_error_ctx *ctx, const char *, const char *error_filename, int error_line);
#else
#define ERROR_REPORT(ctx, error_msg, error_filename, error_line) ((void) 0)
#endif

//bool mbed_error_in_progress;
//static core_util_atomic_flag halt_in_progress = CORE_UTIL_ATOMIC_FLAG_INIT;
//static int error_count = 0;
//static mbed_error_ctx first_error_ctx = {0};
//static mbed_error_ctx last_error_ctx = {0};
//static mbed_error_hook_t error_hook = NULL;

static mbed_error_status_t handle_error(mbed_error_status_t error_status, unsigned int error_value, const char *filename, int line_number, void *caller);

#if MBED_CONF_PLATFORM_CRASH_CAPTURE_ENABLED
//#define report_error_ctx MBED_CRASH_DATA.error.context
//static bool is_reboot_error_valid = false;
#endif

//Helper function to halt the system
static MBED_NORETURN void mbed_halt_system(void)
{
    // Prevent recursion if halt is called again during halt attempt - try
    // something simple instead.

    // In normal context, try orderly exit(1), which eventually calls mbed_die
    exit(1);
}

WEAK MBED_NORETURN void error(const char *format, ...)
{
    // TODO: re-implement
    while(1);
}

/* static inline bool mbed_error_is_hw_fault(mbed_error_status_t error_status)
{
    return 0;
} */


/* static bool mbed_error_is_handler(const mbed_error_ctx *ctx)
{
    return 0;
} */

//Set an error status with the error handling system
static mbed_error_status_t handle_error(mbed_error_status_t error_status, unsigned int error_value, const char *filename, int line_number, void *caller)
{
   // TODO

    return MBED_SUCCESS;
}

WEAK void mbed_error_hook(const mbed_error_ctx *error_context)
{
    //Dont do anything here, let application override this if required.
}

WEAK void mbed_error_reboot_callback(mbed_error_ctx *error_context)
{
    //Dont do anything here, let application override this if required.
}

//Initialize Error handling system and report any errors detected on rebooted
mbed_error_status_t mbed_error_initialize(void)
{
    return MBED_SUCCESS;
}

//Return the first error
mbed_error_status_t mbed_get_first_error(void)
{
    //return the first error recorded
    return 0;
}

//Return the last error
mbed_error_status_t mbed_get_last_error(void)
{
    //return the last error recorded
    return 0;
}

//Gets the current error count
int mbed_get_error_count(void)
{
    //return the current error count
    return 0;
}

//Reads the fatal error occurred" flag
bool mbed_get_error_in_progress(void)
{
    return 0;
}

//Sets a non-fatal error
mbed_error_status_t mbed_warning(mbed_error_status_t error_status, const char *error_msg, unsigned int error_value, const char *filename, int line_number)
{
    return 0;
}

//Sets a fatal error, this function is marked WEAK to be able to override this for some tests
WEAK MBED_NORETURN mbed_error_status_t mbed_error(mbed_error_status_t error_status, const char *error_msg, unsigned int error_value, const char *filename, int line_number)
{ 
    // TODO: re-implement
    while(1);
}

//Register an application defined callback with error handling
MBED_DEPRECATED("Use an overridden mbed_error_hook() function instead")
mbed_error_status_t mbed_set_error_hook(mbed_error_hook_t error_hook_in)
{
    return 0;
}

//Reset the reboot error context
mbed_error_status_t mbed_reset_reboot_error_info()
{
  // TODO
    return MBED_SUCCESS;
}

//Reset the reboot error context
mbed_error_status_t mbed_reset_reboot_count()
{
  // TODO
    return MBED_ERROR_ITEM_NOT_FOUND;
}

//Retrieve the reboot error context
mbed_error_status_t mbed_get_reboot_error_info(mbed_error_ctx *error_info)
{
   // TODO
    return 0;
}

//Retrieve the first error context from error log
mbed_error_status_t mbed_get_first_error_info(mbed_error_ctx *error_info)
{
    // TODO
    return MBED_SUCCESS;
}

//Retrieve the last error context from error log
mbed_error_status_t mbed_get_last_error_info(mbed_error_ctx *error_info)
{
    // TODO
    return MBED_SUCCESS;
}

//Makes an mbed_error_status_t value
mbed_error_status_t mbed_make_error(mbed_error_type_t error_type, mbed_module_type_t entity, mbed_error_code_t error_code)
{
     // TODO
     return 0;
}

/**
 * Clears all the last error, error count and all entries in the error log.
 * @return                      0 or MBED_SUCCESS on success.
 *
 */
mbed_error_status_t mbed_clear_all_errors(void)
{
    return 0;
}


#if MBED_STACK_DUMP_ENABLED
/** Prints stack dump from given stack information.
 * The arguments should be given in address raw value to check alignment.
 * @param stack_start The address of stack start.
 * @param stack_size The size of stack
 * @param stack_sp The stack pointer currently at. */
static void print_stack_dump_core(uint32_t stack_start, uint32_t stack_size, uint32_t stack_sp, const char *postfix)
{

}

static void print_stack_dump(uint32_t stack_start, uint32_t stack_size, uint32_t stack_sp, const mbed_error_ctx *ctx)
{
    // TODO
}
#endif  // MBED_STACK_DUMP_ENABLED

#if MBED_CONF_PLATFORM_ERROR_ALL_THREADS_INFO && defined(MBED_CONF_RTOS_PRESENT)
/* Prints info of a thread(using osRtxThread_t struct)*/
static void print_thread(const osRtxThread_t *thread)
{
        // TODO
}

/* Prints thread info from a list */
static void print_threads_info(const osRtxThread_t *threads)
{
        // TODO
}
#endif

#ifndef NDEBUG
#define GET_TARGET_NAME_STR(tgt_name)   #tgt_name
#define GET_TARGET_NAME(tgt_name)       GET_TARGET_NAME_STR(tgt_name)
//static void print_error_report(const mbed_error_ctx *ctx, const char *error_msg, const char *error_filename, int error_line)
//{
   // TODO
//}
#endif //ifndef NDEBUG


#if MBED_CONF_PLATFORM_ERROR_HIST_ENABLED
//Retrieve the error context from error log at the specified index
mbed_error_status_t mbed_get_error_hist_info(int index, mbed_error_ctx *error_info)
{
        // TODO
}

//Retrieve the error log count
int mbed_get_error_hist_count(void)
{
        // TODO
}

mbed_error_status_t mbed_save_error_hist(const char *path)
{
    // TODO
}
#endif
