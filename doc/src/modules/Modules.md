# Modules theory of operation

##  Function

Every **module** is a dynamic library, which contains functions for emulation of single computer component. **Modules** are meant to be loaded at runtime. Before usage component **instances**, and **interfaces** are created. **Instance** variable holds information about current state of a single component, and **interface** variable contains data on components single input, or output. Those variables have to be destroyed before **module** unload.


## Enumerators

#### **`Error`**

This enumerator is used as return value of module functions. It says whether the function was performed in right way. If an error occur, it informs about error type. The enumerator accepts following values:

| Value | Explanation |
| - | - |
| `SUCCESS`:&nbsp;0 | No error occurred. **Tip:** because `SUCCESS` value is zero, enumerator value can be compared to bool in order to catch errors - `SUCCESS` is `false`, and other values are `true`. |
| `BAD_ARGUMENT`:&nbsp;1 | Invalid argument has been passed to the function (it is possible because sometimes function parameters are void pointers). |
| `MALLOC_ERROR`:&nbsp;2 | Memory allocation failed, e.g. due to insufficient amount of available RAM. |
| SIZE_MISMATCH:3 | Size of given array is insufficient. |


## Global variables

| variable | description |
| - | - |
| `const char*` **`moduleName`** | Contains name of the module. |
| `const char*` **`moduleDescription`** | Contains description of the module |
| `const uint16_t` **`moduleMajorVersion`** | Contains major version of the module. Every major version contains breaking changes. |
| `const uint16_t` **`moduleMinorVersion`** | Contains major version of the module. Minor versios does not contain breaking changes. |
| `const uint16_t` **`protocolVersion`** | Contains version of communitation protocol utilised by module. |
| `const char*` **`interfacesDescriptions`** | Contains descriptions of interfaces created by **`createInterfaces()`** function. |


## Exported Functions

### Functions from `moduleFunctions.c` file

#### **`enum Error getName(char* out, uint32_t maxLength)`**

This function copies module name into a string pointed by **`out`** variable, with length specified by **`maxLength`**.

| Argument | Explanation | Access |
| - | - | - |
| `char* out` | Pointer to array, where module name will be copied. | Write |
| `uint32_t maxLength` | Length of output array. |  |

#### **`enum Error getDescription(char* out, uint32_t maxLength)`**

This function copies module description into a string pointed by **`out`** variable, with length specified by **`maxLength`**.

| Argument | Explanation | Access |
| - | - | - |
| `char* out` | Pointer to array, where module name will be copied. | Write |
| `uint32_t maxLength` | Length of output array. |  |

#### **`uint16_t getMajorVersion()`**

This function returns module major version (every major version contains breaking changes).

#### **`uint16_t getMinorVersion()`**

This function returns module minor version (Minor versios does not contain breaking changes).

#### **`uint16_t getProtocolVersion()`**

This function returns protocol version used by module.

#### **`enum Error getInterfaceDescription(char* out, uint32_t maxLength, uint16_t number)`**

This function copies description for single interface from **`interfacesDesctiptions`** array into a string pointed by **`out`** variable, with length specified by **`maxLength`**.

| Argument | Explaination | Access |
| - | - | - |
| `char* out` | Pointer to array, where module name will be copied. | Write |
| `uint32_t maxLength` | Length of output array. |  |
| `uint16_t number` | Number of interface, which description was requested |  |


### Functions used for emulation

#### **`enum Error create(void* instance, void* parameters)`**

This function creates an component instance.

| Argument | Explanation | Access |
| - | - | - |
| `void** instance` | Pointer to variable, where instance pointer will be stored. | Write |
| `void* parameters` | Pointer to variable, which holds arguments for instance creation. Variable type, and contents are specific for every module | Read |

#### **`enum Error createInterfaces(void* instance, void** interfaces, uint16_t* count)`**

This function creates interfaces of an instance.

| Argument | Explanation | Access |
| - | - | - |
| `void* instance` | Pointer to an instance variable. | Read |
| `void*** interfaces` | Pointer to variable, which will hold interfaces array. | Write |
| `uint16_t* count` | Pointer to variable, in which number of instances created will be stored. Can be used for argument passing, depending on specific module. | Write, Read (optional) |

#### **`enum Error strobeUp(void* instance, void** interfaces)`**

This function executes component change of state for rising edge of the clock.

| Argument | Explanation | Access |
| - | - | - |
| `void* instance` | Pointer to an instance variable. | Read, Write |
| `void** interfaces` | Pointer to module interfaces array. | Read, Write |

#### **`enum Error strobeDown(void* instance, void** interfaces)`**

This function executes component change of state for falling edge of the clock.

| Argument | Explanation | Access |
| - | - | - |
| `void* instance` | Pointer to an instance variable. | Read, Write |
| `void** interfaces` | Pointer to module interfaces array. | Read, Write |

#### **`enum Error destroy(void* instance)`**

This function deallocates instance memory.

| Argument | Explanation | Access |
| - | - | - |
| `void* instance` | Pointer to a variable, where deallocated instance is stored. | Read |

#### **`enum Error destroyInterfaces(void* instance, void** interfaces, uint16_t count)`**

| Argument | Explanation | Access |
| - | - | - |
| `void* instance` | Pointer to a variable, where instance is stored. | Read |
| `void** interfaces` | Pointer to deallocated module interfaces array. | Read |
| `uint16_t count` | Variable containing number of instances provided for deallocation. |
