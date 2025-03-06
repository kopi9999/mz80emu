# Modules theory of operation

##  Function

Every **module** is a dynamic library, which contains functions for emulation of single computer component. **Modules** are meant to be loaded at runtime. Before usage component **instances**, and **interfaces** are created. **Instance** variable holds information about current state of a single component, and **interface** variable contains data on components single input, or output. Those variables have to be destroyed before **module** unload.

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
