# Setting up

## Hardware setup

Porting MCU-Driver-HAL requires the following hardware:

- A development PC running a general purpose operating system such as Windows, macOS or Linux. However, due to limitations of some development tools, a Windows PC  is needed for DAPLink/FlashAlgo development.
- The hardware platform for which MCU-Driver-HAL needs to be ported.
- A micro SD card for the CI test shield.
- A USB cable to connect the hardware platform to the development PC.

If there is no integrated interface chip on the hardware platform you may also need:

- A debug probe, such as [DIPDAP-LPC11U35](https://os.mbed.com/components/DIPDAP-LPC11U35/) that includes a serial interface.
- An additional USB cable.
- An FTDI TTL232R-3V3 USB cable, for the `CONSOLE_TX` and `CONSOLE_RX` pins of the debug probes that do not have a serial connection.

The following items might help you test SPI, I2C and pins:

- A CI test shield v2.0.0. For details, refer to [https://github.com/ARMmbed/ci-test-shield](https://github.com/ARMmbed/ci-test-shield).

<span class="tips">Check the user guide of the evaluation board to see if anything needs to be done prior to using a debug probe and running Mbed OS programs.</span>

## Software setup

Please install the following:

- [Python](https://www.python.org/downloads)
- [Git](https://git-scm.com/downloads)
- [Mbed Tools](https://pypi.org/project/mbed-tools/)
- An IDE and debugger
- [FTDI serial driver](http://www.ftdichip.com/Drivers/VCP.htm) (optional)
