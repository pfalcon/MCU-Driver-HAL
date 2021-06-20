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

int main(void)
{
    gpio_t my_gpio1;
    gpio_t my_gpio2;

    gpio_init_out(&my_gpio1, LED1);
    gpio_init_out(&my_gpio2, LED2);
    
    while (1) {
        gpio_write(&my_gpio1, 1);
        gpio_write(&my_gpio2, 0);
        for (unsigned long i = 0; i < 10000000UL; i++);
        gpio_write(&my_gpio1, 0);
        gpio_write(&my_gpio2, 1);
        for (unsigned long i = 0; i < 10000000UL; i++);
    }
}
