# Modules theory of operation

##  Function

Every **module** is a dynamic library, which contains functions for emulation of single computer component. **Modules** are meant to be loaded at runtime. Before usage component **instances**, and **interfaces** are created. **Instance** variable holds information about current state of a single component, and **interface** variable contains data on components single input, or output. Those variables have to be destroyed before **module** unload.

## Exported Functions

#### **`enum Error create(void* instance, void* parameters)`**

This function creates an component instance.
| Argument | Explaination | Access |
| - | - | - |
| `void* instance` | Pointer to variable, where instance pointer will be stored. | write |
| `void* parameters` | Pointer to variable, which holds arguments for instance creation. Variable type, and contents are specific for every module | Read |

#### **`enum Error createInterfaces(void* instance, void** interfaces, uint16_t* count)`**

This function creates interfaces of an instance.
| Argument | Explaination | Access |
| - | - | - |
| `void* instance` | Pointer to variable, where instance pointer is stored. | Read |
| `void** interfaces` | Pointer to variable, wich will hold pointer to interfaces array. | Write |
| `uint16_t* count` | Pointer to variable, in wich number of instances created will be stored. Can be used for an argument, depending on specific module | Write, Read (optional) |

#### **`enum Error strobeUp(void* instance, void** interfaces)`**

This function executes component change of state for rising edge of the clock

| Argument | Explaination | Access |
| - | - | - |
| `void* instance` | Pointer to a variable, where instance pointer is stored. | Read, Write |
| `void** interfaces` | Pointer to a variable, where module interfaces are stored. | Read, Write |

#### **`enum Error strobeDown(void* instance, void** interfaces)`**

This function executes component change of state for falling edge of the clock

| Argument | Explaination | Access |
| - | - | - |
| `void* instance` | Pointer to a variable, where instance pointer is stored. | Read, Write |
| `void** interfaces` | Pointer to a variable, where module interfaces are stored. | Read, Write |

#### **`enum Error destroy(void* instance)`**

