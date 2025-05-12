# loadConfig.cpp

`loadConfig.cpp` file is responsible for loading and validating data from `config.txt` file. This data can then be used in program, for example to initialization.


## Overview

The file contains one main function named `loadConfig()`. It uses other functions in the file in appropriate way to load data from configuration file and returns it by pointers provided as function arguments.

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


## Functions

### `loadConfig(modules, instanceInfo, interfacesInfo, clockInfo)`

**Returns: `CrashCode`**
| Returned value | Explanation |
| - | - |
| `RUNNING` | Data was loaded correctly. |
| `CONFIG_NOT_FOUND` | Configuration file was not found. |
| `CONFIG_VALUE_NAN` | A value was expected to be an integer, but something else was provided. |
| `CONFIG_VALUE_NOT_BOOL` | A value was expected to be a boolean, but something else was provided. |
| `CONFIG_VALUE_INVALID` | A value was invalid in another way (for example, it was zero when it was not allowed). |
| `CONFIG_INVALID_MODULE_LIST` | The module list was invalid (for example, the same module name was specified more than once). |
| `CONFIG_DERIVED_INTERFACE_INVALID` | A definition of derived interface was invalid (for example, it did not contain "new" word or no value was specified). |
| `CONFIG_INVALID_NUMBER_OF_VALUES` | Number of values in a row was invalid. |
| `CONFIG_ID_DOES_NOT_EXIST` | Specified ID did not exist. |
| `CONFIG_INSTANCE_NUMBER_INCONSISTENT` | Number of values in a section was not equal to number of module instances. |

| Parameter | Explanation |
| - | - |
| `struct Modules* modules` | Pointer to struct where module data will be loaded. |
| `struct InstanceInfo* instanceInfo` | Pointer to struct where data of module instances will be loaded. |
| `struct InterfacesInfo* interfacesInfo` | Pointer to struct where data of interfaces and derived interfaces will be loaded. |
| `struct ClockInfo* clockInfo` | Pointer to struct where data of clock and strobes will be loaded. |

`loadConfig()` function loads and validates data from configuration file. If loading was successful, it saves data in pointers provided as function arguments. However, if data is invalid, these pointers may also contain some data loaded before an error was detected. In case an error was found, the function prints an error message.


### `detectLoadingStep(row)`

**Returns: `LoadingSteps`**

| Parameter | Explanation |
| - | - |
| `string row` | Row of text loaded from configuration file. |

`detectLoadingStep()` checks if row starts with one of the section names which are specified in `config.txt` file documentation. If it contais a name of section, corresponding `LoadingSteps` enumerator is returned. In other case, the function returns `NONE`.


### `loadLineData(row, currentLoadingStep, rawModulesInfo, rawInstanceInfo, rawInterfacesInfo, rawClockInfo)`

**Returns: `CrashCode`** (for an explanation of returned values, see the `loadConfig()` description)

| Parameter | Explanation |
| - | - |
| `string row` | Row of text loaded from configuration file. |
| `enum LoadingSteps currentLoadingStep` | Currently loaded section of configuration file. |
| `vector<string>* rawModulesInfo` | Pointer to the vector where raw module data will be loaded. |
| `vector<string>* rawInstanceInfo` | Pointer to the vector where raw data of module instances will be loaded. |
| `struct RawInterfacesInfo* rawInterfacesInfo` | Pointer to the struct where raw data of interfaces and derived interfaces will be loaded. |
| `struct RawClockInfo* rawClockInfo` | Pointer to the struct where raw data of clock and strobes will be loaded. |

`loadLineData()` saves data from `row` argument in appropriate pointer with raw data. It uses `currentLoadingStep` to decide how to save the data. If `currentLoadingStep` is `NONE` or `NUMBER_OF_STEPS`, no data will be saved. When an error was detected, the function prints an error message.


### `loadDataFromFile(rawModulesInfo, rawInstanceInfo, rawInterfacesInfo, rawClockInfo)`

**Returns: `CrashCode`** (for an explanation of returned values, see the `loadConfig()` description)

| Parameter | Explanation |
| - | - |
| `vector<string>* rawModulesInfo` | Pointer to the vector where raw module data will be loaded. |
| `vector<string>* rawInstanceInfo` | Pointer to the vector where raw data of module instances will be loaded. |
| `struct RawInterfacesInfo* rawInterfacesInfo` | Pointer to the struct where raw data of interfaces and derived interfaces will be loaded. |
| `struct RawClockInfo* rawClockInfo` | Pointer to the struct where raw data of clock and strobes will be loaded. |

`loadDataFromFile()` loads all data from `config.txt` file into pointers with row data. When the configuration file was not found or an error was detected, the function prints an error message.


### `setInstanceData(modules, instanceInfo, rawModulesInfo, rawInstanceInfo)`

**Returns: `CrashCode`** (for an explanation of returned values, see the `loadConfig()` description)

| Parameter | Explanation |
| - | - |
| `struct Modules* modules` | Pointer to struct where module data will be saved. |
| `struct InstanceInfo* instanceInfo` | Pointer to struct where data of module instances will be saved. |
| `vector<string> rawModulesInfo` | Vector where raw module data is stored. |
| `vector<string> rawInstanceInfo` | Vector where raw data of module instances is stored. |

`setInstanceData()` validates raw data of modules and their instances and saves it in pointers passed as function arguments. When an error was detected, the function prints an error message.


### `setInterfacesData(data, instanceCount, rawInterfacesInfo)`

**Returns: `CrashCode`** (for an explanation of returned values, see the `loadConfig()` description)

| Parameter | Explanation |
| - | - |
| `struct InterfacesInfo* data` | Pointer to struct where data of interfaces and derived interfaces will be saved. |
| `uint32_t instanceCount` | Number of module instances. |
| `struct RawInterfacesInfo rawInterfacesInfo` | Struct where raw data of interfaces and derived interfaces is stored. |

`setInterfacesData()` validates raw data of interfaces and derived interfaces and saves it in pointer passed as function argument. When an error was detected, the function prints an error message.


### `setClockData(data, instanceCount, interfacesCount, rawClockInfo)`

**Returns: `CrashCode`** (for an explanation of returned values, see the `loadConfig()` description)

| Parameter | Explanation |
| - | - |
| `struct ClockInfo* data` | Pointer to struct where data of clock and strobes will be saved. |
| `uint32_t instanceCount` | Number of module instances. |
| `uint32_t interfacesCount` | Number of "standard" interfaces (does not include derived interfaces). |
| `struct RawClockInfo rawClockInfo` | Struct where raw data of clock and strobes is stored. |

`setClockData()` validates raw data of clock and strobes and saves it in pointer passed as function argument. When an error was detected, the function prints an error message.