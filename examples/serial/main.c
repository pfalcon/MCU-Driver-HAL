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

#include "serial_api.h"

serial_t my_uart;

int main()
{
    serial_t *serial = &my_uart;
    serial_init(serial, CONSOLE_TX, CONSOLE_RX);
    serial_baud(serial, 115200);

    const char str[] = "Hello world!\n";
    for (unsigned int i = 0; i < sizeof(str); ++i) {
        serial_putc(serial, str[i]);
    }

    while(1){}
}