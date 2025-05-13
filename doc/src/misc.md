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