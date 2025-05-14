# validation.cpp

`validation.cpp` file contains several functions used to validation of config file in `loadConfig.cpp` file.

Validation functions return true, when the input is valid; otherwise, they returns false. All functions in the file print an error message, when the data is invalid. Many of them take an `laodingStep` argument, which should contain the name of the loading step where validation is proceeded - it is printed in the error message.


## Functions

### `validateStringIsInteger(str, loadingStep)`

**Returns: bool**

**Error message:** ERROR: Value "`str`" is not an integer (`loadingStep` section of config.txt).

| Parameter | Explanation |
| - | - |
| `string str` | String which will be checked to see if it is an integer. |
| `string loadingStep` | Name of currently validated loading step. |

`validateStringIsInteger()` checks if the string is an positive integer (contains only digits).


### `validateStringIsBool(str, loadingStep)`

**Returns: bool**

**Error message:** ERROR: Value "`str`" is not a boolean value (`loadingStep` section of config.txt).

| Parameter | Explanation |
| - | - |
| `string str` | String which will be checked to see if it is a boolean. |
| `string loadingStep` | Name of currently validated loading step. |

`validateStringIsBool()` checks if the string is a boolean ("true" or "false"). Letter case does not matter.


### `validateVectorSize(vec, size, loadingStep)`

**Returns: bool**

**Error message:** ERROR: Invalid number of values - "`vec`" - expected `size` values (`loadingStep` section of config.txt).

| Parameter | Explanation |
| - | - |
| `vector<string> vec` | Vector which length will be validated. |
| `size_t size` | Expected size of the vector. |
| `string loadingStep` | Name of currently validated loading step. |

`validateVectorSize()` checks if the vector length is equal to provided value. In the error message, vector elements are displayed one by one, separated by single spaces.