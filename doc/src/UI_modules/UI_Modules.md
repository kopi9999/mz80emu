# UI Modules theory of operation

##  Function

Every **UI module** is a dynamic library, which contains functions for user interaction with the emulator. **UI Modules** are meant to be loaded at runtime. Before usage a **UI instance** (`wxpanel` frpm WX widgets) is created according to the **config** file. Every **UI instance** is tied to corresponding **instance** and **interfaces array** of a compatible **module** with an **UI module**. All **UI instances** are listed in the **Control panel** interface. **UI Instance** must be destroyed before **UI module** unload.

## Enumerators

#### **`Error`**

This enumerator is used as return value of module functions. It says whether the function was performed in right way. If an error occurs, it informs about error type. The enumerator accepts following values:

| Value | Explanation |
| - | - |
| `SUCCESS`:&nbsp;0 | No error occurred. **Tip:** because `SUCCESS` value is zero, enumerator value can be compared to bool in order to catch errors - `SUCCESS` is `false`, and other values are `true`. |
| `BAD_ARGUMENT`:&nbsp;1 | Invalid argument has been passed to the function (it is possible because sometimes function parameters are void pointers). |
| `MALLOC_ERROR`:&nbsp;2 | Memory allocation failed, e.g. due to insufficient amount of available RAM. |
| `SIZE_MISMATCH`:&nbsp;3 | Size of given array is insufficient. |


## Global variables

These variables must be set in the UI module code.

| variable | description |
| - | - |
| `const char*` **`moduleName`** | Contains name of the UI module. |
| `const char*` **`moduleDescription`** | Contains description of the UI module |
| `const uint16_t` **`moduleMajorVersion`** | Contains major version of the UI module. Every major version contains breaking changes. |
| `const uint16_t` **`moduleMinorVersion`** | Contains major version of the UI module. Minor versios does not contain breaking changes. |
| `const uint16_t` **`protocolVersion`** | Contains version of communitation protocol utilised by UI module. |


## Exported Functions

### Functions from `UIModuleFunctions.cpp` file

#### **`enum Error getName(char* out, uint32_t maxLength)`**

This function copies UI module name into a string pointed by **`out`** variable, with length specified by **`maxLength`**.

| Argument | Explanation | Access |
| - | - | - |
| `char* out` | Pointer to array, where UI module name will be copied. | Write |
| `uint32_t maxLength` | Length of output array. |  |

#### **`enum Error getDescription(char* out, uint32_t maxLength)`**

This function copies UI module description into a string pointed by **`out`** variable, with length specified by **`maxLength`**.

| Argument | Explanation | Access |
| - | - | - |
| `char* out` | Pointer to array, where UI module name will be copied. | Write |
| `uint32_t maxLength` | Length of output array. |  |

#### **`uint16_t getMajorVersion()`**

This function returns UI module major version (every major version contains breaking changes).

#### **`uint16_t getMinorVersion()`**

This function returns UI module minor version (Minor versios does not contain breaking changes).

#### **`uint16_t getProtocolVersion()`**

This function returns protocol version used by UI module.


### Functions used for creating UI

#### **`wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces)`**

This function creates an UI instance as a `wxPanel` from WX Widgets, and ties it to the corresponding module **instance** and **interfaces array**. Returns a pointer to thei created panel.

| Argument | Explanation | Access |
| - | - | - |
| `wxControl* parent` | Pointer to a WX Widgets contol, wich is a parent for the created panel. | read |
| `void* instance` | Pointer to the emulator module instance. | read/write |
| `void** interfaces` | Pointer to the emulator module instance's interfaces array | read/write |
