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

## How to compile (For Windows)

Before you try to install the emulator make sure you have Microsoft C++ toolset installed
To compile emulator firstly clone the repositories of the emulator and wxWidgets library

```
git clone https://github.com/kopi9999/mz80emu.git
cd mz80emu
git clone --recurse-submodules https://github.com/wxWidgets/wxWidgets.git
```

Afterwards enter the repository folder. By default it is mz80emu using Native Tools Commands Prompt

```
cd D:\path\to\mz80emu
```

Next create and enter the build folder

```
mkdir build
cd build
```

After that you can compile the program using cmake

```
cmake ..\
cmake --build .\
```

Congratulations you have successfully compiled emulator

## Collaborators

- [kopi9999](https://github.com/kopi9999) - Leader, architect, Module developer
- [Daw151](https://github.com/Daw151) - Module developer
- [Kamil Heinrich](https://github.com/HeinrichKamil) - Ui developer
- [TheDragonEye1](https://github.com/TheDragonEye1) - Ui developer