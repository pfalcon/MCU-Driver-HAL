# Porting guide

This document provides guidelines for adding a new target to MCU-Driver-HAL.


## Index

* Porting process
    * [Setting up](porting_full_process/porting_reqs.md)
    * [Porting](porting_full_process/porting.md)
    * Testing
        * [Testing your port](porting_full_process/built_in_tests.md)
        * [Testing with the demo applications](porting_full_process/demo_testing.md)
        * [Integration tests](porting_full_process/integration-tests.md)
* [Porting the HAL APIs](target/target.md)
    * [Static pin map extension](target/static_pinmap.md)
    * [Low power ticker](target/lp_ticker.md)
    * [Microsecond ticker](target/us_ticker.md)
    * [Standard Pin Names](standard_pin_names/pin_names_porting.md)
    * [RTC](target/rtc.md)
    * [Serial Peripheral Interface (SPI)](target/spi.md)
    * [QuadSPI (QSPI)](target/QuadSPI.md)
    * [Inter-integrated Circuit (I2C)](target/i2c.md)
    * [Flash](target/flash.md)
    * [Thread safety and porting](target/thread_porting.md)
    * [Tickless](target/tickless/tickless.md)
    * [Sleep](target/sleep.md)
    * [ResetReason](target/ResetReason.md)
    * [Watchdog](target/Watchdog.md)
    * [Instrumentation Trace Macrocell](target/itm.md)
    * [MPU](target/mpu.md)
    * [Hardware CRC](target/crc.md)
    * [TRNG](target/trng.md)
* [Porting bootstrap](target/bootstrap.md)
