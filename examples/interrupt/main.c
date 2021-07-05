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
#include "hal/us_ticker_api.h"

#define LED_PERIOD_S 1 // LED1 blinking period in seconds.

gpio_t led1;

void toggle_gpio(gpio_t *gpio)
{
    gpio_write(gpio, gpio_read(gpio) ? 0 : 1);
}

void irq_handler(const ticker_data_t *const ticker)
{
    uint32_t current_tick = ticker->interface->read();
    ticker->interface->clear_interrupt();

    toggle_gpio(&led1);

    const ticker_info_t *info = ticker->interface->get_info();
    uint32_t delay_in_ticks = LED_PERIOD_S * info->frequency;
    uint32_t counter_mask = (1 << info->bits) - 1;
    uint32_t next_irq_tick = (current_tick + delay_in_ticks) & counter_mask;
    ticker->interface->set_interrupt(next_irq_tick);
}

int main()
{
    gpio_init_out(&led1, LED1);
    us_ticker_init();
    set_us_ticker_irq_handler(irq_handler);

    // Force the first interrupt. The following ones will be sheduled
    // by the handler code.
    us_ticker_fire_interrupt();

    while (1);
}