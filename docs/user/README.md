# Getting started

## Prerequisites

### Git

[Git](https://git-scm.com/downloads) is required for acquiring the source code.

### Compiler

A compiler, also known as a toolchain, is required for building the examples, tests, and other code. There are two choices for the compiler/toolchain.

|Compiler | Download | Toolchain Name |
|---------|----------|----------------|
| Arm Compiler 6.15 (default ARM toolchain) | A paid version is available as [Arm Compiler 6.15 Professional](https://developer.arm.com/products/software-development-tools/compilers/arm-compiler/downloads/version-6). A paid version is also included in [Keil MDK 5.33](http://www2.keil.com/mdk5/533) | ARM |
| GNU Arm Embedded version 9 (9-2019-q4-major) | [GNU Arm Embedded version 9 (9-2019-q4-major)](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) | GCC_ARM |

The toolchain name is used in some commands that need to know which compiler is being used.

The open source GNU Arm Embedded compiler is recommended for quick start.

Whichever compiler is chosen, it should be verified that the compiler is in the system path to allow it to be located. For the Arm Compiler, `armclang --version` or with the GNU Arm Embedded compiler, `arm-none-eabi-gcc --version` can be used to verify this.

### Cmake

Use [Cmake](https://cmake.org/download/) v3.19.0 or newer for the build process.

### Build system

As part of the build process, `make`, or an equivalent build system is required. `make` is usually present on Linux distributions, but another build system may need to be installed on MacOS and Windows.  [Ninja](https://ninja-build.org/) is a popular alternative.


If the tool chosen is not the default for your platform, Cmake must be informed using the `CMAKE_GENERATOR` environment variable.

For example, if you want to use ninja, running this before running the cmake configure commands will mean cmake uses ninja for the rest of the session. On linux:
```
$ CMAKE_GENERATOR=Ninja
```

On Windows:
```
> $Env:CMAKE_GENERATOR = "Ninja"
```

This will need to be rerun every time you open a new terminal session. Alternatively, if you wish to make this your permanent default, it can be set in your bash profile, or in windows, it can be added as an environment variable in the same place as your path.

## Additional Prerequisites for running the Greentea tests

In addition to the above, to run the Greentea tests on device, there are some additional prerequisites.


### Python

[Python](https://www.python.org/downloads/) v3.8+ is recommended. Pip (included with all recent versions of Python) is required to install packages.


### mbedhtrun

This tool is part of the [mbed-host-tests](https://pypi.org/project/mbed-host-tests/) Pip package and is required to run the Greentea tests. Once you have Python installed, it can be installed with pip with this command:



```
$ pip3 install mbed-host-tests --upgrade
```

It should be verified that `mbedhtrun` is in the system path. This can be done by running `mbedhtrun --version`.

## Next steps

## Examples and Tests

Check out a partner repository relevant to your hardware to get started with the examples and tests.
[MCU-Driver-ST](https://github.com/MCU-Driver-HAL/MCU-Driver-ST)

### Other Documentation

See the [docs folder](../README.md) for more information.
