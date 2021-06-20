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

#include "hal/PinNameAliases.h"
#include "hal/spi_api.h"

int main()
{
    spi_t spi_object;
    uint8_t ret;
    uint8_t val = 0xAA;

    spi_init(
        &spi_object,
        ARDUINO_UNO_SPI_MOSI,
        ARDUINO_UNO_SPI_MISO,
        ARDUINO_UNO_SPI_SCK,
        ARDUINO_UNO_SPI_CS
    );
    
    ret = spi_master_write(&spi_object, val);

    while(1);
}