# Porting guide

This document provides guidelines for adding a new target to MCU-Driver-HAL.

## Index

* Porting process
    * [Setting up](porting_full_process/porting_reqs.md)
    * [Porting](porting_full_process/porting.md)
    * Testing
        * [Testing your port](porting_full_process/built_in_tests.md)
        * [Testing with the demo applications](porting_full_process/demo_testing.md)
* [Startup configuration](./startup.md)
* [CMake files](./cmake.md)
* [Thread safety and porting](./thread_safety.md)
* Porting the HAL APIs
    * [Serial interface](api/serial.md)
    * [Microsecond ticker](api/us_ticker.md)
    * [Low power ticker](api/lp_ticker.md)
    * [Real-Time Clock (RTC)](api/rtc.md)
    * [Serial Peripheral Interface (SPI)](api/spi.md)
    * [QuadSPI (QSPI)](api/QuadSPI.md)
    * [Inter-integrated Circuit (I2C)](api/i2c.md)
    * [Flash](api/flash.md)
    * [Sleep](api/sleep.md)
    * [ResetReason](api/ResetReason.md)
    * [Watchdog](api/Watchdog.md)
    * [Instrumentation Trace Macrocell (ITM)](api/itm.md)
    * [Memory Protection Unit (MPU)](api/mpu.md)
    * [PinMap](api/pinmap.md)
    * [Standard Pin Names](api/pin_names_porting.md)
    * [Static pin map extension](api/static_pinmap.md)
    * [Hardware CRC](api/crc.md)
    * [TRNG](api/trng.md)

