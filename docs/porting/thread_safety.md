# Thread safety

## Considerations when porting

Drivers that operate below the C HAL layer do not need synchronization mechanisms because this is expected to be provided at a higher level.
The exceptions to this are the following functions:
* `port_read`
* `port_write`
* `gpio_read`
* `gpio_write`

These are expected to use processor specific `set` and `clear` registers rather than performing a read-modify-write sequence.  

## HAL C API

The HAL C API is the porting layer of MCU-Driver-HAL and is not thread safe. Developers should not typically use this API directly. If you program directly to the HAL C API, it is your responsibility to synchronize operations with an appropriate mechanism, such as a mutex.
