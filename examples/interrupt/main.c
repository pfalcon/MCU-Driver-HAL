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

#include "hal/gpio_api.h"
#include "hal/ticker_api.h"

gpio_t my_gpio;

void toggle_handler(uint32_t id)
{
    if (gpio_read(&my_gpio)) gpio_write(&my_gpio, 0);
    else gpio_write(&my_gpio, 1);
}

int main()
{   
    ticker_data_t toggle_ticker;

    gpio_init_out(&my_gpio, LED1);
    
    ticker_set_handler(&toggle_ticker, &toggle_handler);

    while (1);
}