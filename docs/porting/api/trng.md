# True Random Number Generator

The implementation of this interface is specific to your MCU.

## Data structure

You have to define a structure `trng_s` that holds all the information needed to operate the peripheral and describe its state.

## Initialization and release

To enable initializing and releasing the peripheral, you must implement the following functions:

```c
void trng_init(trng_t *obj);
void trng_free(trng_t *obj);
```

## The entropy collector function

The function `trng_get_bytes()` serves as the primary interface to the entropy source. It is expected to load the collected entropy to the buffer and is declared as follows:

```c
int trng_get_bytes(trng_t *obj, uint8_t *output, size_t length, size_t *output_length);
```

- `obj`: A `trng_t`, which is an alias for `trng_s`, and it is the caller's responsibility to initialize it before passing it to this function and release it (with the help of `trng_init()` and `trng_free()`, respectively) when it is not required anymore.

- `output`: a pointer to the output buffer. The function should write the entropy it collected to the buffer; MCU-Driver-HAL uses this data as entropy. Please consult your MCU's manual, and write only the strongest entropy possible in this buffer.

    **Warning:** Although it is possible to fill this buffer without a strong hardware entropy source, we strongly advise against it because it will nullify any security provided by MCU-Driver-HAL.

- `length`: the length of the output buffer. The function should not write more data than this to the output buffer under any circumstances.

- `output_length`: the length of the data written into the output buffer. It tells the caller how much entropy has been collected and how many bytes of the output buffer it can use. It should always reflect the exact amount of entropy collected; setting it higher than the actual number of bytes collected is a serious security risk.

## Indicating the presence of a TRNG

To indicate that the target has an entropy source, you have to add `DEVICE_TRNG=1` in the CMake variable `MBED_TARGET_DEFINITIONS`.
