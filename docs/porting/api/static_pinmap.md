<h1 id="static-pinmap-port">Static pin map extension</h1>

The **static pin map extension** allows you to statically specify the peripheral configuration (pin, peripheral or function) in the HAL API function.

In modern MCUs, you can often map peripherals to different pins, and each pin can have multiple functions. MCU-Driver-HAL supports dynamic pin mapping, meaning you can reconfigure pins at run time for different drivers to use. That provides great flexibility, but it has its drawbacks. There is a nontrivial ROM cost to maintain the pin map tables and infrastructure to parse it. In some use cases, this flexibility is worth the cost. Often, pin configuration is frozen at the hardware design stage and doesn't require run time modification. Shifting this configuration to compile time allows free memory associated with the dynamic approach.

HAL APIs using pins take these pins in their constructor and use those pins to look up which peripheral or function to use. The process of looking up the peripheral or function requires a pin map table that maps pins to peripherals or functions. This pin map table takes up ROM space. The static pin map extension provides additional HAL API constructors, which take pin map as a parameter where the pin, peripheral or function is specified statically, and there is no need to use the pin map tables.

Supported peripherals:

 - `PWM`.
 - `AnalogIn`.
 - `AnalogOut`.
 - `SPI`.
 - `I2C`.
 - `UART`.
 - `QSPI`.
 - `CAN`.
 
## Implementing static pin map extension

If you want to make static pin map available on your platform for a peripheral please follow the steps below:  

1. Provide implementation of `<PERIPHERAL>_init_direct(<PERIPHERAL>_t *obj, static_pinmap_t *)` function and update implementation of `<PERIPHERAL>_init()`.
   - `<PERIPHERAL>_init()` uses pin map tables to determine the associated peripheral or function with the given pins, populates the pin map structure and calls void `<PERIPHERAL>_init_direct()`.
   - `<PERIPHERAL>_init_direct()` performs peripheral initialization using given static pin map structure.

   Example implementation:
   
   ```c
   void <PERIPHERAL>_init_direct(<PERIPHERAL>_t *obj, const PinMap *pinmap) {
       obj->spi.instance = pinmap->peripheral;

       // pin out the <PERIPHERAL> pins
       pin_function(pinmap->pin, pinmap->function);
       pin_mode(pinmap->pin, PullNone);

       // Some additional init code
   }

   void <PERIPHERAL>_init(<PERIPHERAL>_t *obj, PinName pin) {
       int peripheral = (int)pinmap_peripheral(pin, PinMap_<PERIPHERAL>);
       int function = (int)pinmap_find_function(pin, PinMap_<PERIPHERAL>);

       const PinMap static_pinmap = {pin, peripheral, function};

       <PERIPHERAL>_init_direct(obj, &static_pinmap);
   }
   ```

1. Provide a `const` pin map tables in the header file.

   Move pin map tables from `PeripheralPins.c` to `PeripheralPinMaps.h`, and add `const` specifier in the pin map table declarations.

   The tables are required in the header file, so constant expression utility functions can include and use them to find and return mapping without pulling the pin map table into the image.

   Example pin map table:

   ```c
   #include <mstd_cstddef>

   const PinMap PinMap_ADC[] = {
       {.pin=P0_23, .peripheral=ADC0_SE0, .function=0},
       {.pin=P0_10, .peripheral=ADC0_SE1, .function=0},
       {.pin=P0_31, .peripheral=ADC0_SE3, .function=0},
       {.pin=P1_8,  .peripheral=ADC0_SE4, .function=0},
       {.pin=P2_0,  .peripheral=ADC0_SE5, .function=0},
       {.pin=P2_13, .peripheral=ADC0_SE6, .function=0},
       {.pin=P2_11, .peripheral=ADC0_SE7, .function=0},
       {.pin=NC   , .peripheral=NC      , .function=0}
   };
   ```

1. Provide macros for pin map tables.

   Because pin map table names are not common across all MCUs, the following macros for available pin map tables are required in the `PeripheralPinMaps.h` file:

   ```c
   #define PINMAP_ANALOGIN      <PinMap ADC>
   #define PINMAP_ANALOGOUT     <PinMap DAC>
   #define PINMAP_I2C_SDA       <PinMap I2C SDA>
   #define PINMAP_I2C_SCL       <PinMap I2C SCL>
   #define PINMAP_UART_TX       <PinMap UART TX>
   #define PINMAP_UART_RX       <PinMap UART RX>
   #define PINMAP_UART_CTS      <PinMap UART CTS>
   #define PINMAP_UART_RTS      <PinMap UART RTS>
   #define PINMAP_SPI_SCLK      <PinMap SPI SCLK>
   #define PINMAP_SPI_MOSI      <PinMap SPI MOSI>
   #define PINMAP_SPI_MISO      <PinMap SPI MISO>
   #define PINMAP_SPI_SSEL      <PinMap SPI SSEL>
   #define PINMAP_PWM           <PinMap PWM>
   #define PINMAP_QSPI_DATA0    <PinMap QSPI DATA0>
   #define PINMAP_QSPI_DATA1    <PinMap QSPI DATA1>
   #define PINMAP_QSPI_DATA2    <PinMap QSPI DATA2>
   #define PINMAP_QSPI_DATA3    <PinMap QSPI DATA3>
   #define PINMAP_QSPI_SCLK     <PinMap QSPI SCLK>
   #define PINMAP_QSPI_SSEL     <PinMap QSPI SSEL>
   #define PINMAP_CAN_RD        <PinMap CAN RD>
   #define PINMAP_CAN_TD        <PinMap CAN RD>
   ```

1. Provide `STATIC_PINMAP_READY` macro in `PinNames.h`   

   Adding this macro enables the static pin map support for the target.

   ```c
   /* If this macro is defined, you can use constexpr utility functions for pin map search. */
   #define STATIC_PINMAP_READY 1
   ```

## Testing

Use the code below to test the static pin map extension:

```c
int main(void) {
    spi_t spi_object;

    // Regular use
    spi_init(&spi_object, D1, D2, D3, D4);

    // Static pinmap
    const spi_pinmap_t static_spi_pinmap = {
      .peripheral = SPI_1,
      .mosi_pin = D1,
      .mosi_function = 2,
      .miso_pin = D2,
      .miso_function = 2,
      .sclk_pin = D3,
      .sclk_function = 2,
      .ssel_pin = D4,
      .ssel_function = 2
    };
    spi_init_direct(&spi_object, &static_spi_pinmap);

    // Static pinmap with constexpr utility function
    const spi_pinmap_t spi_pinmap = get_spi_pinmap(D1, D2, D3, D4);
    spi_init_direct(&spi_object, &spi_pinmap);

    return 0;
}
```

When you use the static pin map extension, you save on ROM. 

Run FPGA tests to check whether your implementation is valid.

Steps to run the FPGA tests tests will be provided in the future.

<span class="notes">**Note:** Your target must be ready to run FPGA Test Shield tests.</span>
