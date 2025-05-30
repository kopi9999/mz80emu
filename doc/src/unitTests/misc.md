### `testCompareStringVectors` - tests compareStringVectors()

| Test Case Name                         | Input                                        | Expected | Description                   |
| -------------------------------------- | -------------------------------------------- | -------- | ----------------------------- |
| `testCompareStringVectors_equal`       | `{"Hello", "World"}`, `{"Hello", "World"}`   | Pass     | Compare two equal vectors     |
| `testCompareStringVectors_different`   | `{"Hello", "World!"}`, `{"World!", "Hello"}` | Fail     | Compare two different vectors |
| `testCompareStringVectors_emptyVector` | `{}, {}`                                     | Pass     | Compare two empty vectors     |

### `testSplitString` - tests splitString()

| Test Case Name                                | Input                        | Expected                    | Description                          |
| --------------------------------------------- | ---------------------------- | --------------------------- | ------------------------------------ |
| `testSplitString_oneCharDelimiter`            | `"Hello World!"`, `" "`      | `{"Hello", "World"}`        | Split with single char delimiter     |
| `testSplitString_twoCharsDelimiter`           | `"1, 2, 3, 4, 5, "`, `", "`  | `{"1", "2", "3", "4", "5"}` | Split with two character delimiter   |
| `testSplitString_delimiterOnStart`            | `" Hello World!"`, `" "`     | `{"", "Hello", "World!"}`   | Delimiter at the start of the string |
| `testSplitString_delimiterOnEnd`              | `"Hello World! "`, `" "`     | `{"Hello", "World!", ""}`   | Delimiter at the end of the string   |
| `testSplitString_oneCharTwoDelimitersInARow`  | `"Hello  World!"`, `" "`     | `{"Hello", "", "World!"}`   | Two single-char delimiters in a row  |
| `testSplitString_twoCharsTwoDelimitersInARow` | `"Hello    World!"`, `"  "`  | `{"Hello", "", "World!"}`   | Two two-char delimiters in a row     |
| `testSplitString_twoAndHalfDelimiterInARow`   | `"Hello     World!"`, `"  "` | `{"Hello", "", " World!"}`  | Partial delimiter sequence in a row  |
| `testSplitString_halfDelimiterOnStart`        | `" Hello, World!"`, `", "`   | `{" Hello", "World!"}`      | Only part of delimiter at start      |
| `testSplitString_halfDelimiterOnEnd`          | `"Hello, World!,"`, `", "`   | `{"Hello", "World!,"}`      | Only part of delimiter at end        |
| `testSplitString_emptyString`                 | `""`, `" "`                  | `{}`                        | Empty input string                   |
| `testSplitString_emptyDelimiter`              | `"Hello World!"`, `""`       | `{}`                        | Empty delimiter string               |

### `testSplitByWhitespace` - tests splitByWhitespace()

| Test Case Name                                         | Input | Expected | Description                      |
| ------------------------------------------------------ | ----- | -------- | -------------------------------- |
| `testSplitByWhitespace_oneSpace`                       |       | Pass     | String with one space            |
| `testSplitByWhitespace_severalSpaces`                  |       | Pass     | String with multiple spaces      |
| `testSplitByWhitespace_severalVariousChars`            |       | Pass     | Mixed whitespace characters      |
| `testSplitByWhitespace_spaceOnStart`                   |       | Pass     | Leading space                    |
| `testSplitByWhitespace_spaceOnEnd`                     |       | Pass     | Trailing space                   |
| `testSplitByWhitespace_scatteredSingleChars`           |       | Pass     | Mixed whitespace, scattered      |
| `testSplitByWhitespace_scatteredGroupedVariousChars`   |       | Pass     | Grouped various whitespace chars |
| `testSplitByWhitespace_scatteredGroupedRepeatingChars` |       | Pass     | Repeating whitespace groups      |
| `testSplitByWhitespace_noWhitespace`                   |       | Pass     | No whitespace                    |
| `testSplitByWhitespace_onlyWhitespace`                 |       | Pass     | Only whitespace characters       |
| `testSplitByWhitespace_emptyString`                    |       | Pass     | Empty string                     |

### `testToLower` - tests toLower()

| Test Case Name               | Input | Expected | Description              |
| ---------------------------- | ----- | -------- | ------------------------ |
| `testToLower_lowercase`      |       | Pass     | Already lowercase string |
| `testToLower_uppercase`      |       | Pass     | Uppercase string         |
| `testToLower_capitalization` |       | Pass     | Capitalized string       |
| `testToLower_emptyString`    |       | Pass     | Empty string             |

### `testStringToBool` - tests stringToBool()

| Test Case Name                 | Input          | Expected |
| ------------------------------ | -------------- | -------- |
| `testStringToBool_true`        | "true"         | True     |
| `testStringToBool_True`        | "True"         | True     |
| `testStringToBool_TRUE`        | "TRUE"         | True     |
| `testStringToBool_false`       | "false"        | False    |
| `testStringToBool_helloWorld`  | "Hello World!" | False    |
| `testStringToBool_tabulator`   | "\t"           | False    |
| `testStringToBool_emptyString` | ""             | False    |

### `testTrim` - tests trim()

| Test Case Name                    | Input | Expected | Description                  |
| --------------------------------- | ----- | -------- | ---------------------------- |
| `testTrim_spaceOnStart`           |       | Pass     | Leading space                |
| `testTrim_spaceOnEnd`             |       | Pass     | Trailing space               |
| `testTrim_variousWhitespaceChars` |       | Pass     | Mixed whitespace characters  |
| `testTrim_whitespaceInsideString` |       | Pass     | Whitespace inside the string |
| `testTrim_noWhitespace`           |       | Pass     | No whitespace                |
| `testTrim_emptyString`            |       | Pass     | Empty string                 |

### `testTrimLeadingZeros` - tests trimLeadingZeros()

| Test Case Name                        | Input | Expected | Description            |
| ------------------------------------- | ----- | -------- | ---------------------- |
| `testTrimLeadingZeros_oneZero`        |       | Pass     | One leading zero       |
| `testTrimLeadingZeros_severalZeros`   |       | Pass     | Multiple leading zeros |
| `testTrimLeadingZeros_noZeros`        |       | Pass     | No leading zeros       |
| `testTrimLeadingZeros_zeroOnEnd`      |       | Pass     | Zero at the end        |
| `testTrimLeadingZeros_zeroAfterSpace` |       | Pass     | Zero after space       |
| `testTrimLeadingZeros_emptyString`    |       | Pass     | Empty string           |

### `testConvertErrorToCrash` - tests convertErrorToCrash()

| Test Case Name                         | Input | Expected               | Description                |
| -------------------------------------- | ----- | ---------------------- | -------------------------- |
| `testConvertErrorToCrash_SUUCESS`      |       | `RUNNING`              | SUCCESS error code         |
| `testConvertErrorToCrash_BAD_ARGUMENT` |       | `MODULE_BAD_ARGUMENT`  | BAD_ARGUMENT error code    |
| `testConvertErrorToCrash_MALLOC_ERROR` |       | `MODULE_MALLOC_ERROR`  | MALLOC_ERROR code          |
| `testConvertErrorToCrash_invalid`      |       | `MODULE_INVALID_ERROR` | Invalid enum cast          |
| `testConvertErrorToCrash_NULL`         |       | `RUNNING`              | NULL pointer cast as error |

### `testFirstNullPointer` - tests firstNullPointer()

| Test Case Name                           | Input | Expected       | Description          |
| ---------------------------------------- | ----- | -------------- | -------------------- |
| `testFirstNullPointer_nullPointerInside` |       | Index 3        | NULL inside array    |
| `testFirstNullPointer_firstNullPointer`  |       | Index 0        | NULL at index 0      |
| `testFirstNullPointer_lastNullPointer`   |       | Index 4        | NULL at last index   |
| `testFirstNullPointer_noNullPointer`     |       | Index 5 (size) | No NULL in array     |
| `testFirstNullPointer_arrayNullr`        |       | Index 0        | Array itself is NULL |