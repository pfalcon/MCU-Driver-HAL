# Testing with the demo applications

You can use two applications to test your port:

1. When you've ported GPIO (and all preceeding modules), use `mbed-os-example-blinky`.

## mbed-os-example-blinky

1. Application repository: [https://github.com/ARMmbed/mbed-os-example-blinky](https://github.com/ARMmbed/mbed-os-example-blinky).
1. Import the repo, if you haven't done this already while porting:

    ```
    mbed import https://github.com/ARMmbed/mbed-os-example-blinky.git
    cd mbed-os-example-blinky
    ```
1. If your target has not been merged into `mbed-os`, replace `mbed-os` with your fork. (Change the URL to match your repository.)

    ```
    mbed remove mbed-os
    mbed add https://github.com/ARMmbed/mbed-os-new-target mbed-os
    ```

1. Build the image:

    ```
    mbed compile -m <new_target> -t gcc_arm
    ```
1. Flash the image (.bin or .hex) to the board.
1. Verify the designated LED flashes every 0.5 second. You can use an oscilloscope for accurate measurement.
