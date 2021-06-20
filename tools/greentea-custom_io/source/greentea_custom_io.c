/*
 * Copyright (c) 2021 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "greentea-client/test_io.h"
#include "greentea-custom_io/custom_io.h"
#include "hal/serial_api.h"

extern serial_t stdio_uart;

void greentea_init_custom_io(void)
{
    serial_init(&stdio_uart, CONSOLE_TX, CONSOLE_RX);
    serial_baud(&stdio_uart, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);
}

int greentea_getc(void)
{
    return serial_getc(&stdio_uart);
}

void greentea_putc(int c)
{
    serial_putc(&stdio_uart, c);
}

void greentea_write_string(const char *str)
{
    while (*str != '\0') {
        serial_putc(&stdio_uart, *str++);
    }
}
