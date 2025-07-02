# misc.cpp

`misc.cpp` file contains several functions useful in various situations.


## Functions

### `compareStringVectors(vec1, vec2)`

**Returns: bool**

| Parameter | Explanation |
| - | - |
| `vector<string> vec1` | First vector of strings to compare. |
| `vector<string> vec2` | Second vector of strings to compare. |

`compareStringVectors()` checks if both vectors passed as function arguments are identical. It returns false when vectors vary in length or any pair of elements with the same ID in both vectors does not consist of identical elements. When no defference was found, the function returns true.


### `splitString(str, delimiter)`

**Returns: `vector<string>`**

| Parameter | Explanation |
| - | - |
| `string str` | String to split. |
| `string delimiter` | String which separates individual string fragments. |

`splitString()` splits a string passed as a function argument using the given delimiter. Every element of returned vector is a fragment of provided string. The string is divided at each position where the delimiter occurs. Thus no element of the vector contains the delimiter.

When the delimiter is located at the beginning or end of the string, it is also split - in that situation the first or the last element of the vector is empty string. Two delimiters in a row also results in separation of empty string.

When provided string or delimiter is an empty string, the function returns an empty vector.


### `splitByWhitespace(str)`

**Returns: `vector<string>`**

| Parameter | Explanation |
| - | - |
| `string str` | String to split. |

`splitByWhitespace()` splits a string passed as a function argument using whitespace characters as a delimiter. A returned vector contains separate words included in the string. The whitespace characters include: " " (space), "\n" (new line), "\r" (carriage return) and "\t" (tab).

Several whitespace characters are recognized as a simple delimiter. When any whitespace characters are located at the beginning or end of the string, they are ignored.

When provided string is an empty string, the function returns an empty vector.


### `toLower(str)`

**Returns: string**

| Parameter | Explanation |
| - | - |
| `string str` | String to convert to lowercase. |

`toLower()` converts all uppercase characters in the provided string to lowercase and returns the resulting string.


### `stringToBool(str)`

**Returns: bool**

| Parameter | Explanation |
| - | - |
| `string str` | String to convert to boolean. |

`stringToBool()` checks if the given string is "true". If this is the case, the function returns true; otherwise, it returns false. The letter case does not matter - the function uses `toLower()` function to convert the string to lowercase.


### `boolToString(boolean)`

**Returns: string**

| Parameter | Explanation |
| - | - |
| `bool boolean` | Boolean to convert to string. |

`boolToString()` returns the string `"true"` when `boolean` is true, and `"false"` otherwise.


### `trim(str)`

**Returns: void**

| Parameter | Explanation |
| - | - |
| `string* str` | Pointer to string which will be trimmed. |

`trim()` removes all whitespace characters from the beginning and end of the provided string. The whitespace characters include: " " (space), "\n" (new line), "\r" (carriage return) and "\t" (tab).


### `trimLeadingZeros(str)`

**Returns: void**

| Parameter | Explanation |
| - | - |
| `string* str` | Pointer to string which will be trimmed. |

`trimLeadingZeros()` removes all zero characters from the beginning of the provided string.


### `convertErrorToCrash(error)`

**Returns: `CrashCode`**

| Parameter | Explanation |
| - | - |
| `enum Error error` | `Error` enumerator which will be converted to `CrashCode` enumerator. |

| Argument | Returned value |
| - | - |
| `SUCCESS` | `RUNNING` |
| `BAD_ARGUMENT` | `MODULE_BAD_ARGUMENT` |
| `MALLOC_ERROR` | `MODULE_MALLOC_ERROR` |
| other value | `MODULE_INVALID_ERROR` |

`convertErrorToCrash()` returns a `CrashCode` enumerator basing on which `Error` enumerator was provided as a function argument.


### `setCrashIfRunning(crashVar, crash)`

**Returns: void**

| Parameter | Explanation |
| - | - |
| `enum CrashCode* crashVar` | Pointer to variable which `CrashCode` value would be changed. |
| `enum CrashCode crash` | `CrashCode` which would be set as value of `crashVar`. |

`setCrashIfRunning()` checks whether the value of `crashVar` is `RUNNING`. If so, `crashVar` value is changed to provided `crash`. Otherwise, nothing happens.