# init

`init.cpp` file is responsible for for loading modules, creating instances, and interfaces specified in `config.txt` file, which is read and interpreted by `loadConfig.cpp`.

## Overview

The file contains `init` function, which supplies data to sub-functions:

- loadLibs - loads modules into memory
- loadModuleFunctions - loads needed functions from modules
- loadInstances - creates module instances
- loadInterfaces - creates interfaces from instances
- loadDerivedInterfaces - creates derived interfaces

## Functions

### `init(struct Modules* modules, void*** instances, void**** interfaces, struct InstanceInfo instanceInfo, struct InterfacesInfo interfacesInfo)`

Returns: `CrashCode`

| Returned value                           | Explanation                                                  |
| ---------------------------------------- | ------------------------------------------------------------ |
| `RUNNING`                                | function finished successfully                               |
| `INIT_MODULE_NOT_FOUND`                  | at least one of specified modules was not found              |
| `INIT_MODULE_INVALID`                    | at least one of modules does not contain at least one of the required functions specified in the module protocol |
| `INIT_INSTANCE_CREATION_ERROR`           | at least one of the instances could not have been  created   |
| `INIT_INTERFACES_CREATION_ERROR`         | at least one of interfaces tables could not have been  created |
| `INIT_DERIVED_INTERFACES_CREATION_ERROR` | at least one of derived interfaces tables could not have  been created |

| Parameter                              | Explanation                                                  |
| -------------------------------------- | ------------------------------------------------------------ |
| `struct Modules* modules`              | pointer to a struct, where module names, pointers, and function pointers are stored |
| `void*** instances`                    | pointer to instances array, which stores instance pointers   |
| `void**** interfaces`                  | pointer to interfaces array, which stores interface array pointers |
| `struct InstanceInfo instanceInfo`     | struct containing information about instances                |
| `struct InterfacesInfo interfacesInfo` | struct containing information about interfaces               |

`init` function supplies data to its sub-functions. It manages the order of data loading, and handles error codes.

### `loadLibs(void** libs, vector<string> libNames, uint16_t libCount)`

Returns: `bool`
| Parameter                 | Explanation                                                  |
| ------------------------- | ------------------------------------------------------------ |
| `void** libs`             | pointer to an array, which is being filled with module pointers |
| `vector<string> libNames` | string vector, which holds module file names                 |
| `uint16_t libCount`       | unsigned integer containing number of modules to load        |

`loadLibs` function loads modules into memory. If any module could not have been loaded, the function unloads modules, and returns `false`.

### `loadModuleFunctions(struct Modules modules)`

Returns: `bool`
| Parameter                | Explanation                                                  |
| ------------------------ | ------------------------------------------------------------ |
| `struct Modules modules` | struct, where module names, pointers, and function pointers are stored. This function stores module function pointers here. |

`loadModuleFunctions` loads functions from modules. If any function could not have been loaded, the function unloads modules, and returns `false`.

### `loadInstances(struct Modules modules, void** instances, struct InstanceInfo instanceInfo)`

Returns: `bool`
| Parameter                          | Explanation                                                  |
| ---------------------------------- | ------------------------------------------------------------ |
| `struct Modules modules`           | struct, where module names, pointers, and function pointers are stored |
| `void** instances`                 | array, where instance pointers will be stored                |
| `struct InstanceInfo instanceInfo` | struct containing information about instances                |

`loadInstances` function creates instances specified in `instanceInfo`. When an instance could not have been loaded, returns `false`.

### `loadInterfaces(struct Modules modules, void** instances, void*** interfaces, const uint32_t* instancesList, struct InterfacesInfo interfacesInfo)`

Returns: `bool`
| Parameter                              | Explanation                                                  |
| -------------------------------------- | ------------------------------------------------------------ |
| `struct Modules modules`               | struct, where module names, pointers, and function pointers are stored |
| `void** instances`                     | array, where instance pointers will be stored                |
| `void**** interfaces`                  | pointer to interfaces array, which stores interface array pointers |
| `const uint32_t* instancesList`        | pointer to unsigned int, which holds IDs of instances. variable from InstanceInfo struct |
| `struct InterfacesInfo interfacesInfo` | struct containing information about interfaces               |

`loadInterfaces` creates module interfaces specified in `interfacesInfo`. When a module interface array could not have been loaded, returns `false`.

### `loadDerivedInterfaces(void*** interfaces, struct InterfacesInfo interfacesInfo)`

Returns: `bool`

| Parameter                              | Explanation                                                  |
| -------------------------------------- | ------------------------------------------------------------ |
| `void**** interfaces`                  | pointer to interfaces array, which stores interface array pointers |
| `struct InterfacesInfo interfacesInfo` | struct containing information about interfaces               |

`loadDerivedInterfaces` creates derived interfaces specified in `interfacesInfo`. When a derived interface array could not have been loaded, returns `false`.