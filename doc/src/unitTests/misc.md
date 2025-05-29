### `testCompareStringVectors`

| Test Case Name                         | Description                   | Expected Result |
| -------------------------------------- | ----------------------------- | --------------- |
| `testCompareStringVectors_equal`       | Compare two equal vectors     | Pass            |
| `testCompareStringVectors_different`   | Compare two different vectors | Fail            |
| `testCompareStringVectors_emptyVector` | Compare two empty vectors     | Pass            |

### `testSplitString`

| Test Case Name                                | Description                          | Expected Result |
| --------------------------------------------- | ------------------------------------ | --------------- |
| `testSplitString_oneCharDelimiter`            | Split with single char delimiter     | Pass            |
| `testSplitString_twoCharsDelimiter`           | Split with two character delimiter   | Pass            |
| `testSplitString_delimiterOnStart`            | Delimiter at the start of the string | Pass            |
| `testSplitString_delimiterOnEnd`              | Delimiter at the end of the string   | Pass            |
| `testSplitString_oneCharTwoDelimitersInARow`  | Two single-char delimiters in a row  | Pass            |
| `testSplitString_twoCharsTwoDelimitersInARow` | Two two-char delimiters in a row     | Pass            |
| `testSplitString_twoAndHalfDelimiterInARow`   | Partial delimiter sequence in a row  | Pass            |
| `testSplitString_halfDelimiterOnStart`        | Only part of delimiter at start      | Pass            |
| `testSplitString_halfDelimiterOnEnd`          | Only part of delimiter at end        | Pass            |
| `testSplitString_emptyString`                 | Empty input string                   | Pass            |
| `testSplitString_emptyDelimiter`              | Empty delimiter string               | Pass            |

### `testSplitByWhitespace`

| Test Case Name                                         | Description                      | Expected Result |
| ------------------------------------------------------ | -------------------------------- | --------------- |
| `testSplitByWhitespace_oneSpace`                       | String with one space            | Pass            |
| `testSplitByWhitespace_severalSpaces`                  | String with multiple spaces      | Pass            |
| `testSplitByWhitespace_severalVariousChars`            | Mixed whitespace characters      | Pass            |
| `testSplitByWhitespace_spaceOnStart`                   | Leading space                    | Pass            |
| `testSplitByWhitespace_spaceOnEnd`                     | Trailing space                   | Pass            |
| `testSplitByWhitespace_scatteredSingleChars`           | Mixed whitespace, scattered      | Pass            |
| `testSplitByWhitespace_scatteredGroupedVariousChars`   | Grouped various whitespace chars | Pass            |
| `testSplitByWhitespace_scatteredGroupedRepeatingChars` | Repeating whitespace groups      | Pass            |
| `testSplitByWhitespace_noWhitespace`                   | No whitespace                    | Pass            |
| `testSplitByWhitespace_onlyWhitespace`                 | Only whitespace characters       | Pass            |
| `testSplitByWhitespace_emptyString`                    | Empty string                     | Pass            |

### `testToLower`

| Test Case Name               | Description              | Expected Result |
| ---------------------------- | ------------------------ | --------------- |
| `testToLower_lowercase`      | Already lowercase string | Pass            |
| `testToLower_uppercase`      | Uppercase string         | Pass            |
| `testToLower_capitalization` | Capitalized string       | Pass            |
| `testToLower_emptyString`    | Empty string             | Pass            |

### `testStringToBool`

| Test Case Name                 | Description              | Expected Result |
| ------------------------------ | ------------------------ | --------------- |
| `testStringToBool_true`        | Input "true"             | True            |
| `testStringToBool_True`        | Input "True"             | True            |
| `testStringToBool_TRUE`        | Input "TRUE"             | True            |
| `testStringToBool_false`       | Input "false"            | False           |
| `testStringToBool_helloWorld`  | Input "Hello World!"     | False           |
| `testStringToBool_tabulator`   | Input with tab character | False           |
| `testStringToBool_emptyString` | Empty string             | False           |

### `testTrim`

| Test Case Name                    | Description                  | Expected Result |
| --------------------------------- | ---------------------------- | --------------- |
| `testTrim_spaceOnStart`           | Leading space                | Pass            |
| `testTrim_spaceOnEnd`             | Trailing space               | Pass            |
| `testTrim_variousWhitespaceChars` | Mixed whitespace characters  | Pass            |
| `testTrim_whitespaceInsideString` | Whitespace inside the string | Pass            |
| `testTrim_noWhitespace`           | No whitespace                | Pass            |
| `testTrim_emptyString`            | Empty string                 | Pass            |

### `testTrimLeadingZeros`

| Test Case Name                        | Description            | Expected Result |
| ------------------------------------- | ---------------------- | --------------- |
| `testTrimLeadingZeros_oneZero`        | One leading zero       | Pass            |
| `testTrimLeadingZeros_severalZeros`   | Multiple leading zeros | Pass            |
| `testTrimLeadingZeros_noZeros`        | No leading zeros       | Pass            |
| `testTrimLeadingZeros_zeroOnEnd`      | Zero at the end        | Pass            |
| `testTrimLeadingZeros_zeroAfterSpace` | Zero after space       | Pass            |
| `testTrimLeadingZeros_emptyString`    | Empty string           | Pass            |

### `testConvertErrorToCrash`

| Test Case Name                         | Description                | Expected Result        |
| -------------------------------------- | -------------------------- | ---------------------- |
| `testConvertErrorToCrash_SUUCESS`      | SUCCESS error code         | `RUNNING`              |
| `testConvertErrorToCrash_BAD_ARGUMENT` | BAD_ARGUMENT error code    | `MODULE_BAD_ARGUMENT`  |
| `testConvertErrorToCrash_MALLOC_ERROR` | MALLOC_ERROR code          | `MODULE_MALLOC_ERROR`  |
| `testConvertErrorToCrash_invalid`      | Invalid enum cast          | `MODULE_INVALID_ERROR` |
| `testConvertErrorToCrash_NULL`         | NULL pointer cast as error | `RUNNING`              |

### `testFirstNullPointer`

| Test Case Name                           | Description          | Expected Result |
| ---------------------------------------- | -------------------- | --------------- |
| `testFirstNullPointer_nullPointerInside` | NULL inside array    | Index 3         |
| `testFirstNullPointer_firstNullPointer`  | NULL at index 0      | Index 0         |
| `testFirstNullPointer_lastNullPointer`   | NULL at last index   | Index 4         |
| `testFirstNullPointer_noNullPointer`     | No NULL in array     | Index 5 (size)  |
| `testFirstNullPointer_arrayNullr`        | Array itself is NULL | Index 0         |