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


## Exported Functions

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
