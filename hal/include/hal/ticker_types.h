/* Copyright (c) 2021 Arm Limited
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

/** \addtogroup hal */
/** @{*/

#ifndef TICKER_TYPES_H
#define TICKER_TYPES_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Legacy format representing a timestamp in us.
 * Given it is modeled as a 32 bit integer, this type can represent timestamp
 * up to 4294 seconds (71 minutes).
 * Prefer using us_timestamp_t which store timestamp as 64 bits integer.
 */
typedef uint32_t timestamp_t;

/** Information about the ticker implementation
 */
typedef struct {
    uint32_t frequency;                           /**< Frequency in Hz this ticker runs at */
    uint32_t bits;                                /**< Number of bits this ticker supports */
} ticker_info_t;

/** Ticker's interface structure - required API for a ticker
 */
typedef struct {
    void (*init)(void);                           /**< Init function */
    uint32_t (*read)(void);                       /**< Read function */
    void (*disable_interrupt)(void);              /**< Disable interrupt function */
    void (*clear_interrupt)(void);                /**< Clear interrupt function */
    void (*set_interrupt)(timestamp_t timestamp); /**< Set interrupt function */
    void (*fire_interrupt)(void);                 /**< Fire interrupt right-away */
    void (*free)(void);                           /**< Disable function */
    const ticker_info_t *(*get_info)(void);       /**< Return info about this ticker's implementation */
    bool runs_in_deep_sleep;                      /**< Whether ticker operates in deep sleep */
} ticker_interface_t;

typedef struct ticker_data_s ticker_data_t;
typedef void (*ticker_irq_handler_type)(const ticker_data_t *const);

#if !MBED_CONF_USE_TICKER_EVENT_QUEUE

struct ticker_data_s {
    const ticker_interface_t *interface; /**< Ticker's interface */
};

#endif // !MBED_CONF_USE_TICKER_EVENT_QUEUE

#endif

/** @}*/
