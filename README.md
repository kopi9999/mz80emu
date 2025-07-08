# mz80emu - Work in progress

Modular computer emulator


## Overview

Mz80emu is a computer emulator. Every component is emulated by separate dynamic library, which is linked at runtime. Connections between components are specified in config. Thanks to that, the program can simulate various computer architectures, and other synchronous digital devices.

## Advantages and Limitations

### ✅ Advantages
- **Modular architecture** – Each component is a separate dynamic library, allowing for flexibility and easy expansion.
- **Multi-platform potential** – While the project is currently Windows-focused, its modular design could allow for Linux/MacOS support in the future.
- **Support for multiple architectures** – Thanks to configurable connections between modules, the emulator can potentially simulate various computer architectures and synchronous digital devices.
- **Open-source and extensible** – Developers can contribute new modules and extend existing functionality.
- **CMake build system** – Simplifies compilation and dependency management.

### ⚠️ Limitations
- **Work in progress** – The project is still under heavy development, and some features may be missing or unstable.
- **Windows-only build (for now)** – No official support for Linux/MacOS yet, although it may be possible in the future.
-  **No GUI (yet)** – The emulator currently lacks a full graphical user interface, making it harder for non-technical users to interact with it.
-  **Performance optimizations needed** – The emulator might not be optimized for speed, especially for complex architectures.
-  **Limited documentation** – While the README provides basic setup instructions, more in-depth documentation is needed.

## How to compile

### For GNU/Linux

Before compiling the emulator make sure you have at least requred dependencies installed.

#### Downloading dependencies on Debian 12

| Required | Optional |
| - | - |
| `sudo apt install git cmake g++ libwxgtk3.2-dev` | `sudo apt install libboost-test-dev` |

#### Downloading dependencies on Debian Arch Linux

| Required | Optional |
| - | - |
| `sudo pacman -S git cmake make gcc wxwidgets-gtk3` | `sudo pacman -S boost` |

To compile emulator firstly clone the emulator repository using git.

```
git clone https://github.com/kopi9999/mz80emu.git
cd mz80emu
```

After that create the build folder, enter it and compile the project using cmake and GNU make.

```
mkdir build
cd build
cmake ..
make
```

Congratulations you have successfully compiled mz80emu for GNU/Linux.

### For Windows

Before you try to compile the emulator make sure you have Microsoft C++ toolset installed.

To compile emulator firstly clone the repositories of the emulator and wxWidgets library.

```
git clone https://github.com/kopi9999/mz80emu.git
cd mz80emu
git clone --recurse-submodules https://github.com/wxWidgets/wxWidgets.git
```

For optional tests compilation, download `boost` library. Next, create `boost` folder in the root folder of mz80emu, and copy the contents of the library. It is required for the library headers to be in `mz80emu\boost\boost`. Compilation is not needed.

Enter the root mz80emu folder using Native Tools Commands Prompt, create and enter the build folder.

```
cd D:\path\to\mz80emu
mkdir build
cd build
```

After that you can compile the program using cmake.

```
cmake ..\
cmake --build .\
```

Congratulations you have successfully compiled mz80emu for Windows.

## Collaborators

- [kopi9999](https://github.com/kopi9999)
- [Daw151](https://github.com/Daw151)
- [Kamil Heinrich](https://github.com/HeinrichKamil)
- [TheDragonEye1](https://github.com/TheDragonEye1)
