# main.cpp

`main.cpp` file is responsible for running emulator by initialization of all necessary modules and supervising clock. It contains:
- variables storing data of modules, their instances and interfaces,
- defintions of types used to storing pointers to functions in arrays,
- definition of struct containing modules data.


## Functions

### `main()`
`main()` function takes care of loading essential data, correct processing it and running main loop.

At first, function loads data from configuration files and saves it in proper variables and arrays thanks to `loadConfig()` function.

When loading is completed, program loads all modules DLL libraries, creates pointers to their functions and creates instances of modules and interfaces basing on data taken from configuration files. For this purpose it uses `init()` function.

To store the data, there are used `modules`, `instanceInfo`, `interfacesInfo` and `clockInfo` structs.

Then, variables used to simulate clock are created. They consists of `clockState` (storing current clock state), `start`, `end` and `duration` variables used for changing clock state at proper time with `chrono::high_resolution_clock`.

Finally, a main loop starts. In each iteration it calls `strobeUp()` and `strobeDown()` functions of all module instances. Next, program waits for the appropriate amount of time and increments `clockState` variable or changes its value to zero in case when it is equal to `clockDepth`, meaning number of clock states.

If an error occurs when program tries to load module, get pointer to module function, create module instance or interface, or any of `strobeUp()` and `strobeDown()` functions returns error, all libraries are unloaded with `unloadLibs()` function and `main()` stops.



# main.hpp

`main.hpp` file contains definitions of enumerations, structs and types, which are useful in `main.cpp` file or in the whole program.


## Type definitions

There are several type definitions in the file, which are used to storing pointers to functions of modules.
| Type | Indicated function |
| - | - |
| `createPtr` | `create()` |
| `createInterfacesPtr` | `createInterfaces()` |
| `strobeUpPtr` | `strobeUp()` |
| `strobeDownPtr` | `strobeDown()` |
| `destroyPtr` | `destroy()` |
| `destroyInterfacesPtr` | `destroyInterfaces()` |


## Enumerations

### `CrashCode`

`CrashCode` enumeration contains codes of errors which can occur while the program is running. First of them - `RUNNING` code - means that no error occured, every other code indicates on a specific error type. Codes are divided into categories, which base on the time and place of an error occurence - they are marked as the beginning of enumerator name.

| Category | Meaning |
| - | - |
| `CONFIG` | An error occurred while the configuration file was being loaded. |
| `INIT` | An error occurred during initialization of modules and interfaces. |
| `MODULE` | An error occurred when an operation of module instance failed. |


## Structs

### `Modules`
`Modules` is struct used to create `modules` variable storing all data concerning modules (not to be confused with module instances). Its fields includes:
| Field | Explanation |
| - | - |
| `names` | Vector of all modules names (with added .dll extension), so that it can be used to recognise specific module DLL libraries. |
| `count` | Number of modules. |
| `pointers` | Array of pointers to loaded DLL libraries. |
| `createFuncs`</br>`createInterfacesFuncs`</br>`strobeUpFuncs`</br>`strobeDownFuncs`</br>`destroyFuncs`</br>`destroyInterfacesFuncs` | Arrays of pointers to modules functions having names corresponding to names of these arrays. |

In case of arrays and vectors, values at a given index in all of them correspond to the same specific module.

### `DerivedInterfaceIds`
Struct which stores data of an interface in a derived interface array.
| Field | Explanation |
| - | - |
| `interfacesId` | ID of the interface array. |
| `interfaceId` | ID of the interface in that array. |

### `InstanceInfo`
`InstanceInfo` stores data of all module instances.
| Field | Explanation |
| - | - |
| `count` | Number of module instances. |
| `list` | Array of modules IDs. There will be created one instance of module with given ID for all IDs in this array. |
| `parameters` | Array of parameters of each instance. |

### `InterfacesInfo`
`InterfacesInfo` stores data of all interfaces and derived interfaces.
| Field | Explanation |
| - | - |
| `count` | Number of standard interface arrays. |
| `derivedCount` | Number of derived interface arrays. |
| `totalCount` | Number of all interface arrays. |
| `list` | Array of module instances IDs. There will be created one interface array basing on instance with given ID for all IDs in this array. |
| `derivedList` | Two-dimensional array of `DerivedInterfaceIds` structs. The outer array stores data of all derived interface arrays and the inner arrays symbolize specific derived interface array. Inner arrays comprise structs which refer to specific interfaces. |
| `lengths` | Array storing lengths of each standard interface array. |
| `derivedLengths` | Array storing lengths of each derived interface array. |

### `ClockInfo`
`ClockInfo` stores clock period, clock depth and strobes data.
| Field | Explanation |
| - | - |
| `period` | Time between clock ticks in nanoseconds. |
| `depth` | Number of clock states. |
| `strobeUpInstanceList` | Array of all module instances indicating an order of calling their `strobeUp()` functions. `strobeUp()` of first element of this array will be called first. |
| `strobeUpInterfacesList` | Array of interface arrays which will be used when `strobeUp()` function is called. When `strobeUp()` is called the first time, the first interface array from this array will be used. |
| `strobeUpClock` | Two-dimensional array of boolean values. It indicates the clock states at which the `strobeUp()` function will be called. The outer array stores data of all module instances and the inner arrays stores booleans meaning whether `strobeUp()` of the instance will be called at specific clock state. Number of boolean values in one inner array is equal to the clock depth. |
| `strobeDownInstanceList` | Analogous to the `strobeUpInstanceList`. |
| `strobeDownInterfacesList` | Analogous to the `strobeUpInterfacesList`. |
| `strobeDownClock` | Analogous to the `strobeUpClock`. |