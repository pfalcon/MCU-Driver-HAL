<h1 id="pinmap-port">PinMap</h1>

All HAL APIs that use pins have functions to get the corresponding pin maps. These functions return a `PinMap` array with each entry containing a pin name, a peripheral and a function. The presence of an NC pin indicates the end of the pin map array. Below is an example implementation of the function to get the serial transmit pin map:

```c
const PinMap PinMap_UART_TX[] = {
    {P0_19, UART_0, 1},
    {P1_13, UART_0, 3},
    {P1_27, UART_0, 2},
    { NC  , NC    , 0}
};

const PinMap *serial_tx_pinmap(void) {
    return PinMap_UART_TX;
}
```

MCU that do not use a pin map, such as the ones with peripherals that can connect to any pin, must still define pin maps because testing requires them. 
For these devices, the pin map does not need to be comprehensive. Instead, it should list a representative sample of pins and peripherals, so they can be tested appropriately. Please see the [static pin map extension documentation](./static_pinmap.md) for information about how to statically specify the peripheral configuration in the HAL API function.

## Testing

MCU-Driver-HAL provides a set of conformance tests for all HAL APIs. You can use these tests to validate the correctness of your implementation.

Steps to run the HAL tests will be provided in the future.

### FPGA

You can test your port using the FPGA test shield component.

Steps to run the HAL FPGA tests shield will be provided in the future.
