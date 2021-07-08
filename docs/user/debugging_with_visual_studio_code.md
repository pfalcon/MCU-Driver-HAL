# Debugging with Visual Studio Code

The popular Visual Studio Code editor for Windows, Linux and macOS can be used in your development process to debug source code. It allows a local debug toolchain to be configured, this guide will mostly focus on debugging with pyOCD. pyOCD is a Python package for programming and debugging Arm Cortex-M microcontrollers.

---
**Note:**

Other on-chip debugging software, such as OpenOCD, can also be used by replacing the commands specific to pyOCD (in the debugger configuration file) with those for the debugging software of your choice.

---

## Prerequisites
* Install the GNU Arm Embedded toolchain
* Install CMake
* Install Visual Studio Code
* Install Visual Studio Code C/C++ extension by Microsoft
* Install the pyOCD Python package 

---
**Note:**

Ensure pyOCD and the GNU Arm Embedded toolchain can be executed from any location in your command line interface. You may need to ensure their installation paths are added to your operating systems `PATH` environment variable or equivalent.

---

## Configuring the debugger for pyOCD
The steps below describe how to setup the debugger for Visual Studio Code. `${workspaceRoot}` refers to the root of your project workspace. For this guide, `${workspaceRoot}` is assumed to be the root of a Silicon partner's SDK repository which also includes a reference to the `MCU-Driver-HAL` repository.

1. Create your configuration by clicking the `create a launch.json file` link in the `RUN` view after clicking on the `Run and Debug` button on the left of Visual Studio Code.
The `launch.json` file is located in a `.vscode` folder in your workspace (project root folder) or in your user settings or workspace settings.
1. Open the `.vscode/launch.json` file and add the example configurations below:
    ```JSONC
    {
        // Use IntelliSense to learn about possible attributes.
        // Hover to view descriptions of existing attributes.
        // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
        "version": "0.2.0",
        "configurations": [
            {
                "name": "Build and debug",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceRoot}/relative/path/to/artefact.elf",
                "args": [],
                "stopAtEntry": true,
                "cwd": "${workspaceRoot}",
                "environment": [],
                "externalConsole": false,
                "debugServerArgs": "",
                "serverLaunchTimeout": 20000,
                "filterStderr": true,
                "filterStdout": false,
                "serverStarted": "GDB\\ server\\ started",
                "preLaunchTask": "cmake_build",
                "setupCommands": [
                    { "text": "-target-select remote localhost:3333", "description": "connect to target", "ignoreFailures": false },
                    { "text": "-file-exec-and-symbols ${workspaceRoot}/relative/path/of/directory/containing/elf/artefact.elf", "description": "load file", "ignoreFailures": false},
                    { "text": "-interpreter-exec console \"monitor endian little\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor reset\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor halt\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor arm semihosting enable\"", "ignoreFailures": false },
                    { "text": "-target-download", "description": "flash target", "ignoreFailures": false }
                ],
                "logging": {
                    "moduleLoad": true,
                    "trace": true,
                    "engineLogging": true,
                    "programOutput": true,
                    "exceptions": true
                },
                "linux": {
                    "MIMode": "gdb",
                    "MIDebuggerPath": "arm-none-eabi-gdb",
                    "debugServerPath": "pyocd",
                    "debugServerArgs": "gdbserver"
                },
                "osx": {
                    "MIMode": "gdb",
                    "MIDebuggerPath": "arm-none-eabi-gdb",
                    "debugServerPath": "pyocd",
                    "debugServerArgs": "gdbserver"
                },
                "windows": {
                    "preLaunchTask": "cmake_build",
                    "MIMode": "gdb",
                    "MIDebuggerPath": "arm-none-eabi-gdb.exe",
                    "debugServerPath": "pyocd.exe",
                    "debugServerArgs": "gdbserver",
                    "setupCommands": [
                        { "text": "-environment-cd ${workspaceRoot}\\relative\\path\\of\\directory\\containing\\elf" },
                        { "text": "-target-select remote localhost:3333", "description": "connect to target", "ignoreFailures": false },
                        { "text": "-file-exec-and-symbols artefact.elf", "description": "load file", "ignoreFailures": false},
                        { "text": "-interpreter-exec console \"monitor endian little\"", "ignoreFailures": false },
                        { "text": "-interpreter-exec console \"monitor reset\"", "ignoreFailures": false },
                        { "text": "-interpreter-exec console \"monitor halt\"", "ignoreFailures": false },
                        { "text": "-interpreter-exec console \"monitor arm semihosting enable\"", "ignoreFailures": false },
                        { "text": "-target-download", "description": "flash target", "ignoreFailures": false }
                    ]
                }
            }
        ]
    }
    ```

    Where:
    * `\\relative\\path\\of\\directory\\containing\\elf` or `/relative/path/of/directory/containing/elf/` is the path of the directory containing the ELF file to debug relative to `${workspaceRoot}`.
    * `artefact.elf` is the ELF file to debug

    ---
    **Note:**

    The `type` must be `cppvsdbg` when using the Visual Studio Windows debugger.
    For more information on each field visit https://code.visualstudio.com/docs/cpp/launch-json-reference

    ---

## Configuring build generator
This ensures the build output to debug matches the current state of the source code by rebuilding if any changes to the code were made.

1. From Visual Studio Code Command Palette (`Ctrl+Shift+P` on Windows and Linux, `⇧⌘P` on MacOS), type:
    ```
    >task
    ```
1. Select `Tasks: Configure Default Build Task` to create a template `tasks.json` file resembling:
    ```JSONC
    {
        // See https://go.microsoft.com/fwlink/?LinkId=733558
        // for the documentation about the tasks.json format
        "version": "2.0.0",
        "tasks": [
            {
                "label": "echo",
                "type": "shell",
                "command": "echo Hello",
                "problemMatcher": [],
                "group": {
                    "kind": "build",
                    "isDefault": true
                }
            }
        ]
    }
    ```
1. Modify the `tasks.json` file to look as follows to create a task to build the artefacts:
    ```JSONC
    {
        // See https://go.microsoft.com/fwlink/?LinkId=733558
        // for the documentation about the tasks.json format
        "version": "2.0.0",
        "tasks": [
            {
                "label": "cmake_build",
                "type": "shell",
                "options": {
                    "cwd": "${workspaceRoot}/relative/path/of/directory/containing/application/main/CMakeLists/file"
                },
                "command": "cmake",
                "args": [
                    "-S",
                    ".",
                    "-B",
                    "cmake_build",
                    "-G",
                    "Ninja",
                    "-D",
                    "CMAKE_BUILD_TYPE=debug",
                    "-D",
                    "MBED_TOOLCHAIN=GCC_ARM",
                    "&&",
                    "cmake",
                    "--build",
                    "cmake_build"
                ],
                "problemMatcher": [],
                "group": {
                    "kind": "build",
                    "isDefault": true
                }
            }
        ]
    }
    ```
    where `/relative/path/of/directory/containing/application/main/CMakeLists/file` is the path to the directory containing the application to debug main `CMakeLists.txt` file relative to `${workspaceRoot}`.

    Ensure the task's `label` matches the `preLaunchTask` in `launch.json` so the command specified is executed before the debug session is started.

## Starting a debug session

1. Connect the hardware to debug to the host computer using a USB cable.
1. In the `RUN` view after clicking on the `Run and Debug` button on the left of Visual Studio Code, press the play button to start the debug session. If the source code has been modified or the build output has not yet been generated, a build output is generated and programmed on to the target hardware before lauching the debug session.
