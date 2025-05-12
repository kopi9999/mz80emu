# loadConfig.cpp

`loadConfig.cpp` file is responsible for loading and validating data from `config.txt` file. This data can then be used in program, for example to initialization.

## Overview

The file contains one main function named `loadConfig`. It uses other functions in the file in appropriate way to load data from configuration file and returns it by pointers provided as function arguments.

At the beginning the function checks if `config.txt` file exists. Then, it loads data from this file line by line. Simultaneously, there is performed a first part of validation. Each line is validated instantly after loading. When the line is invalid, loading is canceled. First part of validation detects such errors as passing a text when a number is expected or incorrect number of values.

Data immediately after loading and initial validation is still not suitable for use. So next begins a second part of validation and parallel loading data to appropriate pointers. This part of validation can detect errors impossible to find before the enitre data is loaded. They include, among others: an ID which does not exist or situation when number of values in corresponding sections is not equal. This part is also performed "line by line" - program validates one part of data and if it is valid, it is loaded to pointer with data ready to use.

When the configuration file cannot be found or its structure is invalid, the function returns an error code from `CrashCode` enumeration. When all operations have been processed correctly, it returns `RUNNING` code.

## Enumerations

### `LoadingSteps`
Enumeration used to marking which section of config file is currently being loaded. It also stores a number of possible sections thanks to `NUMBER_OF_STEPS` value.
| Enumerator | Value | Explanation |
| - | - | - |
| `NONE` | 0 | Used as current section when loading starts. It means that no section has started yet. Data is not loaded when the current section is `NONE`. |
| Names of configuration file sections, for example `MODULES` or `MODULE_INSTANCES`. | various | Each "standard" enumerator of `LoadingSteps` refers to one section of `config.txt` file. Thanks to that, the program knows which variable the data should be loaded into. |
| `NUMBER_OF_STEPS` | one more than the number of sections | This enumerator does not indicate any section. However, its value depends on number of sections, so it can be useful when the number of sections is needed. |

## Structs

### `RawInterfacesInfo`
Stores data of interfaces and derived interfaces after loading and first part of validation.
| Field | Corresponding section in configuration file | Explanation |
| - | - | - |
| `module` | `Interfaces` | Vector of all "standard" interfaces. |
| `derived` | `Derived interfaces` | Three-dimensional vector of derived interfaces. Outer vector length is equal to number of derived interfaces, each middle vector length is a number of values stored in derived interface and each inner vector stores two numbers, which refer to ID of "standard" interface and ID of its sub-element. |

### `RawClockInfo`
Stores clock period, clock depth and all data of strobe up and strobe down after loading and first part of validation.
| Field | Corresponding section in configuration file | Explanation |
| - | - | - |
| `period` | `Clock period` | Time between clock ticks in nanoseconds, stored as string. |
| `depth` | `Clock depth` | Number of clock states, stored as string. |
| `strobeUpInstances` | `Strobe up instances` | Vector of IDs of module instances, which stores an order of calling `strobeUp()` of these instances. |
| `strobeUpInterfaces` | `Strobe up interfaces` | Vector of IDs of interfaces, which are used when `strobeUp()` is called. |
| `strobeUpClock` | `Strobe up clock` | Two-dimensional vector of strings. Outer vector length is number of module instances and each inner vector length is equal to clock depth. Inner vectors store boolean values describing on which clock states `strobeUp()` is called. |
| `strobeDownInstances` | `Strobe down instances` | See `strobeUpInstances`. |
| `strobeDownInterfaces` | `Strobe down interfaces` | See `strobeUpInterfaces`. |
| `strobeDownClock` | `Strobe down clock` | See `strobeUpClock`. |