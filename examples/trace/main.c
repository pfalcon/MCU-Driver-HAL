/* Copyright (c) 2020-2021 Arm Limited
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

#define MBED_CONF_MBED_TRACE_ENABLE 1
#define MBED_TRACE_MAX_LEVEL TRACE_LEVEL_DEBUG
#define TRACE_GROUP "main"

#include "serial_api.h"
#include "mbed_trace.h"

extern serial_t stdio_uart;

void serial_print(const char *string)
{
    while (*string != 0) {
        serial_putc(&stdio_uart, *string++);
    }
    serial_putc(&stdio_uart, '\n');
}

int main()
{
    serial_init(&stdio_uart, CONSOLE_TX, CONSOLE_RX);
    serial_baud(&stdio_uart, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);

    mbed_trace_init();
    mbed_trace_print_function_set(serial_print);

    tr_debug("This is a debug trace!");
    tr_info("This is an info trace!");
    tr_warn("This is a warning trace!");
    tr_err("This is an error trace!");

    while (1);
}
