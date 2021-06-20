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

/** \addtogroup hal */
/** @{*/

#ifndef MBED_GPIO_API_H
#define MBED_GPIO_API_H

#include <stdint.h>
#include "device.h"
#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

#if DEVICE_PORTIN || DEVICE_PORTOUT

/** Port HAL structure. port_s is declared in the target's HAL
 */
typedef struct port_s port_t;

/**
 * \defgroup hal_port Port HAL functions
 * @{
 */

/** Get the pin name from the port's pin number
 *
 * @param port  The port name
 * @param pin_n The pin number within the specified port
 * @return The pin name for the port's pin number
 */
PinName port_pin(PortName port, int pin_n);

/** Initilize the port
 *
 * @param obj  The port object to initialize
 * @param port The port name
 * @param mask The bitmask to identify which bits in the port should be included (0 - ignore)
 * @param dir  The port direction
 */
void port_init(port_t *obj, PortName port, int mask, PinDirection dir);

/** Set the input port mode
 *
 * @param obj  The port object
 * @param mode THe port mode to be set
 */
void port_mode(port_t *obj, PinMode mode);

/** Set port direction (in/out)
 *
 * @param obj The port object
 * @param dir The port direction to be set
 */
void port_dir(port_t *obj, PinDirection dir);

/** Write value to the port
 *
 * @param obj   The port object
 * @param value The value to be set
 */
void port_write(port_t *obj, int value);

/** Read the current value on the port
 *
 * @param obj The port object
 * @return An integer with each bit corresponding to an associated port pin setting
 */
int port_read(port_t *obj);

#endif // DEVICE_PORTIN || DEVICE_PORTOUT

#if DEVICE_INTERRUPTIN

/** GPIO IRQ events
 */
typedef enum {
    IRQ_NONE,
    IRQ_RISE,
    IRQ_FALL
} gpio_irq_event;

/** GPIO IRQ HAL structure. gpio_irq_s is declared in the target's HAL
 */
typedef struct gpio_irq_s gpio_irq_t;

typedef void (*gpio_irq_handler)(uint32_t id, gpio_irq_event event);

/**
 * \defgroup hal_gpioirq GPIO IRQ HAL functions
 *
 * # Defined behavior
 * * ::gpio_irq_init initializes the GPIO IRQ pin
 * * ::gpio_irq_init attaches the interrupt handler
 * * ::gpio_irq_free releases the GPIO IRQ pin
 * * ::gpio_irq_set enables/disables pin IRQ event
 * * ::gpio_irq_enable enables GPIO IRQ
 * * ::gpio_irq_disable disables GPIO IRQ
 *
 * # Undefined behavior
 * * Calling other function before ::gpio_irq_init
 *
 * @{
 */

/** Initialize the GPIO IRQ pin
 *
 * @param obj     The GPIO object to initialize
 * @param pin     The GPIO pin name
 * @param handler The handler to be attached to GPIO IRQ
 * @param id      The object ID (id != 0, 0 is reserved)
 * @return -1 if pin is NC, 0 otherwise
 */
int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id);

/** Release the GPIO IRQ PIN
 *
 * @param obj The gpio object
 */
void gpio_irq_free(gpio_irq_t *obj);

/** Enable/disable pin IRQ event
 *
 * @param obj    The GPIO object
 * @param event  The GPIO IRQ event
 * @param enable The enable flag
 */
void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable);

/** Enable GPIO IRQ
 *
 * This is target dependent, as it might enable the entire port or just a pin
 * @param obj The GPIO object
 */
void gpio_irq_enable(gpio_irq_t *obj);

/** Disable GPIO IRQ
 *
 * This is target dependent, as it might disable the entire port or just a pin
 * @param obj The GPIO object
 */
void gpio_irq_disable(gpio_irq_t *obj);

/** Get the pins that support all GPIO IRQ tests
 *
 * Return a PinMap array of pins that support GPIO IRQ.
 * The array is terminated with {NC, NC, 0}.
 *
 * Targets should override the weak implementation of this
 * function to provide the actual pinmap for GPIO IRQ testing.
 *
 * @return PinMap array
 */
const PinMap *gpio_irq_pinmap(void);

/**@}*/

#endif // DEVICE_INTERRUPTIN

/**
 * \defgroup hal_gpio GPIO HAL functions
 *
 * # Defined behavior
 * * ::gpio_init and other init functions can be called with NC or a valid PinName for the target - Verified by ::gpio_nc_test
 * * ::gpio_is_connected can be used to test whether a gpio_t object was initialized with NC - Verified by ::gpio_nc_test
 * * ::gpio_init initializes the GPIO pin
 * * ::gpio_free returns the pin owned by the GPIO object to its reset state
 * * ::gpio_mode sets the mode of the given pin
 * * ::gpio_dir sets the direction of the given pin
 * * ::gpio_write sets the gpio output value
 * * ::gpio_read reads the input value
 * * ::gpio_init_in inits the input pin and sets mode to PullDefault
 * * ::gpio_init_in_ex inits the input pin and sets the mode
 * * ::gpio_init_out inits the pin as an output, with predefined output value 0
 * * ::gpio_init_out_ex inits the pin as an output and sets the output value
 * * ::gpio_init_inout inits the pin to be input/output and set pin mode and value
 * * The GPIO operations ::gpio_write, ::gpio_read take less than 20us to complete
 * * The function ::gpio_get_capabilities fills the given
 * `gpio_capabilities_t` instance according to pin capabilities.
 *
 * # Undefined behavior
 * * Calling any ::gpio_mode, ::gpio_dir, ::gpio_write or ::gpio_read on a gpio_t object that was initialized
 *   with NC.
 * * Calling ::gpio_set with NC.
 *
 * @{
 */

/**
 * \defgroup hal_gpio_tests GPIO HAL tests
 * The GPIO HAL tests ensure driver conformance to defined behaviour.
 *
 * To run the GPIO hal tests use the command:
 *
 *     mbed test -t <toolchain> -m <target> -n tests-mbed_hal_fpga_ci_test_shield-gpio,tests-mbed_hal-gpio
 *
 */

/** GPIO capabilities for a given pin
 */
typedef struct {
    uint8_t pull_none : 1;
    uint8_t pull_down : 1;
    uint8_t pull_up : 1;
} gpio_capabilities_t;

/** Set the given pin as GPIO
 *
 * @param pin The pin to be set as GPIO
 * @return The GPIO port mask for this pin
 **/
uint32_t gpio_set(PinName pin);

/** Checks if gpio object is connected (pin was not initialized with NC)
 * @param obj The GPIO object
 * @return 0 if object was initialized with NC
 * @return non-zero if object was initialized with a valid PinName
 **/
int gpio_is_connected(const gpio_t *obj);

/** Initialize the GPIO pin
 *
 * @param obj The GPIO object to initialize
 * @param pin The GPIO pin to initialize (may be NC)
 */
void gpio_init(gpio_t *obj, PinName pin);

/** Releases the GPIO pin
 *
 * @param obj The GPIO object to release
 */
void gpio_free(gpio_t *obj);

/** Set the input pin mode
 *
 * @param obj  The GPIO object (must be connected)
 * @param mode The pin mode to be set
 */
void gpio_mode(gpio_t *obj, PinMode mode);

/** Set the pin direction
 *
 * @param obj       The GPIO object (must be connected)
 * @param direction The pin direction to be set
 */
void gpio_dir(gpio_t *obj, PinDirection direction);

/** Set the output value
 *
 * @param obj   The GPIO object (must be connected)
 * @param value The value to be set
 */
void gpio_write(gpio_t *obj, int value);

/** Read the input value
 *
 * @param obj The GPIO object (must be connected)
 * @return An integer value 1 or 0
 */
int gpio_read(gpio_t *obj);

// the following functions are generic and implemented in the common gpio.c file
// TODO: fix, will be moved to the common gpio header file

/** Init the input pin and set mode to PullDefault
 *
 * @param gpio The GPIO object
 * @param pin  The pin name (may be NC)
 */
void gpio_init_in(gpio_t *gpio, PinName pin);

/** Init the input pin and set the mode
 *
 * @param gpio  The GPIO object
 * @param pin   The pin name (may be NC)
 * @param mode  The pin mode to be set
 */
void gpio_init_in_ex(gpio_t *gpio, PinName pin, PinMode mode);

/** Init the output pin as an output, with predefined output value 0
 *
 * @param gpio The GPIO object
 * @param pin  The pin name (may be NC)
 * @return     An integer value 1 or 0
 */
void gpio_init_out(gpio_t *gpio, PinName pin);

/** Init the pin as an output and set the output value
 *
 * @param gpio  The GPIO object
 * @param pin   The pin name (may be NC)
 * @param value The value to be set
 */
void gpio_init_out_ex(gpio_t *gpio, PinName pin, int value);

/** Init the pin to be in/out
 *
 * @param gpio      The GPIO object
 * @param pin       The pin name (may be NC)
 * @param direction The pin direction to be set
 * @param mode      The pin mode to be set
 * @param value     The value to be set for an output pin
 */
void gpio_init_inout(gpio_t *gpio, PinName pin, PinDirection direction, PinMode mode, int value);

/** Fill the given gpio_capabilities_t instance according to pin capabilities.
 */
void gpio_get_capabilities(gpio_t *gpio, gpio_capabilities_t *cap);

/** Get the pins that support all GPIO tests
 *
 * Return a PinMap array of pins that support GPIO. The
 * array is terminated with {NC, NC, 0}.
 *
 * Targets should override the weak implementation of this
 * function to provide the actual pinmap for GPIO testing.
 *
 * @return PinMap array
 */
const PinMap *gpio_pinmap(void);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif

/** @}*/
