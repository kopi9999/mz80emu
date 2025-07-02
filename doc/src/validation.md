# validation.cpp

`validation.cpp` file contains several functions used to validation of config file in `loadConfig.cpp` file.

Validation functions return true, when the input is correct; otherwise, they returns false. All functions in the file print an error message, when the data is invalid. Many of them take an `laodingStep` argument, which should contain the name of the loading step where validation is proceeded - it is printed in the error message.


## Functions

### `validateStringIsInteger(str, loadingStep)`

**Returns: bool** (true when the string is an integer, otherwise false)

**Error message:** ERROR: Value "`str`" is not an integer ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `string str` | String which will be checked to see if it is an integer. |
| `string loadingStep` | Name of currently validated loading step. |

`validateStringIsInteger()` checks if the string is an non-negative integer (contains only digits).


### `validateStringIsBool(str, loadingStep)`

**Returns: bool** (true when the string is a boolean, otherwise false)

**Error message:** ERROR: Value "`str`" is not a boolean value ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `string str` | String which will be checked to see if it is a boolean. |
| `string loadingStep` | Name of currently validated loading step. |

`validateStringIsBool()` checks if the string is a boolean ("true" or "false"). Letter case does not matter.


### `validateVectorSize(vec, size, loadingStep)`

**Returns: bool** (true when the vector size is correct, otherwise false)

**Error message:** ERROR: Invalid number of values - "`vec`" - expected `size` values ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `vector<string> vec` | Vector whose length will be validated. |
| `size_t size` | Expected size of the vector. |
| `string loadingStep` | Name of currently validated loading step. |

`validateVectorSize()` checks if the vector length is equal to provided value. In the error message, vector elements are displayed one by one, separated by single spaces.


### `validateDerivedInterfaceCreated(loadedDerivedInterfaces)`

**Returns: bool** (true when a derived interface array has been created, otherwise false)

**Error message:** ERROR: New derived interface array has not been created, but its interfaces were specified ("Derived interfaces" section of config.txt).

| Parameter | Explanation |
| - | - |
| `vector<vector<vector<string>>> loadedDerivedInterfaces` | Vector of derived interface arrays. |

`validateDerivedInterfaceCreated()` checks if any derived interface arrays have been created. For this purpose it checks whether the number of derived interface arrays is greater than zero. In this way it is possible to detect the syntax error when values of the array are specified without the "new" word.


### `validateDerivedInterfaceHasValues(derivedInterface)`

**Returns: bool** (true when the derived interface array has values, otherwise false)

**Error message:** ERROR: New derived interface array has been created, but its interfaces were not specified ("Derived interfaces" section of config.txt).

| Parameter | Explanation |
| - | - |
| `vector<vector<string>> derivedInterface` | Vector of derived interface arrays. |

`validateDerivedInterfaceHasValues()` checks if the derived interface array has at least one value. It can detect the syntax error when the "new" word occurs without any specified value.


### `validateIdExist(id, maxId, loadingStep)`

**Returns: bool** (true when the ID exists, otherwise false)

**Error message:** ERROR: Specified ID "`id`" does not exist ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `uint32_t id` | ID which will be validated. |
| `uint32_t maxId` | Maximum accepted value of ID. |
| `string loadingStep` | Name of currently validated loading step. |

`validateIdExist()` checks if an ID passed as function argument exists. In this purpose it uses the maximum possible value of ID - when `id` is greater than `maxId`, it does not exist. That verification is possible because IDs always start at zero.


### `validateValueDoesNotEqualZero(value, loadingStep)`

**Returns: bool** (true when the integer is greater than zero, otherwise false)

**Error message:** ERROR: Specified value equals zero ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `uint32_t value` | Non-negative integer which will be validated. |
| `string loadingStep` | Name of currently validated loading step. |

`validateValueDoesNotEqualZero()` checks if the integer is greater than zero.


### `validateValueEqualsNumberOfInstances(value, numberOfInstances, loadingStep)`

**Returns: bool** (true when the integer is greater than zero, otherwise false)

**Error message:** ERROR: Number of values in section does not equal number of instances ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `uint32_t value` | Non-negative integer which will be validated. |
| `uint32_t numberOfInstances` | Number of module instances. |
| `string loadingStep` | Name of currently validated loading step. |

`validateValueEqualsNumberOfInstances()` checks if the integer is equal to the number of module instances.


### `validateVectorHasUniqueValues(vec, loadingStep)`

**Returns: bool** (true when all values in the vector are unique, otherwise false)

**Error message:** ERROR: Values in section are not unique ("`loadingStep`" section of config.txt).

| Parameter | Explanation |
| - | - |
| `vector<string> vec` | Vector whose values will be checked to ensure they are unique. |
| `string loadingStep` | Name of currently validated loading step. |

`validateVectorHasUniqueValues()` checks if values in the vector do not repeat. If any two elements of the vector are identical, the function returns false.

All values are converted using `trimLeadingZeros()` function from `misc.cpp` file (only inside the function, it does not affect on the original vector). For this reason values differing only by number of leading zeros are recognized as identical (for example, "1" and "001" are the same value from the point of view of validation).