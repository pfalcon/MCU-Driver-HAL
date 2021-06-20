/****************************************************************************
 * Copyright (c) 2015, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************
 */

#include "utest/utest_shim.h"
#include "utest/utest_stack_trace.h"

// only one callback is active at any given time
static volatile utest_v1_harness_callback_t minimal_callback;

static int32_t utest_minimal_init(void)
{
    UTEST_LOG_FUNCTION();
    minimal_callback = NULL;
    return 0;
}

static void *utest_minimal_post(const utest_v1_harness_callback_t callback, timestamp_t delay_ms)
{
    UTEST_LOG_FUNCTION();
    minimal_callback = callback;
    // this scheduler does not support scheduling of asynchronous callbacks
    return (delay_ms ? NULL : (void*)1);
}

static int32_t utest_minimal_cancel(void *handle)
{
    UTEST_LOG_FUNCTION();
    (void) handle;
    // this scheduler does not support canceling of asynchronous callbacks
    return -1;
}

static int32_t utest_minimal_run(void)
{
    UTEST_LOG_FUNCTION();
    /* This is the amazing minimal scheduler.
     * This is just a busy loop that calls the callbacks in this context.
     * THIS LOOP IS BLOCKING.
     */
    while(1)
    {
        // check if a new callback has been set
        if (minimal_callback) {
            // copy the callback
            utest_v1_harness_callback_t callback = minimal_callback;
            // reset the shared callback
            minimal_callback = NULL;
            // execute the copied callback
            callback();
        }
    }
    return 0;
}

extern "C" {

static const utest_v1_scheduler_t utest_minimal_scheduler =
{
    utest_minimal_init,
    utest_minimal_post,
    utest_minimal_cancel,
    utest_minimal_run
};

utest_v1_scheduler_t utest_v1_get_scheduler()
{
    UTEST_LOG_FUNCTION();
    return utest_minimal_scheduler;
}

}
