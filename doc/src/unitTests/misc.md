### `testCompareStringVectors` - tests compareStringVectors()

| Test Case Name                         | Input                                        | Expected | Description                   |
| -------------------------------------- | -------------------------------------------- | -------- | ----------------------------- |
| `testCompareStringVectors_equal`       | `{"Hello", "World"}`, `{"Hello", "World"}`   | `true`   | Compare two equal vectors     |
| `testCompareStringVectors_different`   | `{"Hello", "World!"}`, `{"World!", "Hello"}` | `false`  | Compare two different vectors |
| `testCompareStringVectors_emptyVector` | `{}, {}`                                     | `true`   | Compare two empty vectors     |

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
| `testSplitByWhitespace_oneSpace`                       | `"Hello World!"` | `{"Hello", "World!"}` | String with one space            |
| `testSplitByWhitespace_severalSpaces`                  | `"Hello   World!"` | `{"Hello", "World!"}` | String with multiple spaces      |
| `testSplitByWhitespace_severalVariousChars`            | `"Hello\r \t\nWorld!"` | `{"Hello", "World!"}` | Mixed whitespace characters      |
| `testSplitByWhitespace_spaceOnStart`                   | `" HelloWorld!"` | `{"HelloWorld!"}` | Leading space                    |
| `testSplitByWhitespace_spaceOnEnd`                     | `"HelloWorld! "` | `{"HelloWorld!"}` | Trailing space                   |
| `testSplitByWhitespace_scatteredSingleChars`           | `"Hello World!\nHello\tWorld! Hello\rWorld!"` | `{"Hello", "World!", "Hello", "World!", "Hello", "World!"}` | Mixed whitespace, scattered      |
| `testSplitByWhitespace_scatteredGroupedVariousChars`   | `"Hello \tWorld!\n\rHello \nWorld!"` | `{"Hello", "World!", "Hello", "World!"}` | Grouped various whitespace chars |
| `testSplitByWhitespace_scatteredGroupedRepeatingChars` | `"Hello\t\tWorld!\n\nHello  World!\r\rHello  World!"` | `{"Hello", "World!", "Hello", "World!", "Hello", "World!"}` | Repeating whitespace groups      |
| `testSplitByWhitespace_noWhitespace`                   | `"HelloWorld!"` | `{"HelloWorld!"}` | No whitespace                    |
| `testSplitByWhitespace_onlyWhitespace`                 | `" \n\r\t"` | `{}` | Only whitespace characters       |
| `testSplitByWhitespace_emptyString`                    | `""` | {}   | Empty string                     |

### `testToLower` - tests toLower()

| Test Case Name               | Input            | Expected         | Description              |
| ---------------------------- | ---------------- | ---------------- | ------------------------ |
| `testToLower_lowercase`      | `"hello world!"` | `"hello world!"` | Already lowercase string |
| `testToLower_uppercase`      | `"HELLO WORLD!"` | `"hello world!"` | Uppercase string         |
| `testToLower_capitalization` | `"Hello World!"` | `"hello world!"` | Capitalized string       |
| `testToLower_emptyString`    | `""`             | `""`             | Empty string             |

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

| Test Case Name                    | Input                         | Expected         | Description                  |
| --------------------------------- | ----------------------------- | ---------------- | ---------------------------- |
| `testTrim_spaceOnStart`           | `" HelloWorld!"`              | `"HelloWorld!"`  | Leading space                |
| `testTrim_spaceOnEnd`             | `"HelloWorld! "`              | `"HelloWorld!"`  | Trailing space               |
| `testTrim_variousWhitespaceChars` | `"\r\t \nHelloWorld! \n\t\r"` | `"HelloWorld!"`  | Mixed whitespace characters  |
| `testTrim_whitespaceInsideString` | `"Hello World!"`              | `"Hello World!"` | Whitespace inside the string |
| `testTrim_noWhitespace`           | `"HelloWorld!"`               | `"HelloWorld!"`  | No whitespace                |
| `testTrim_emptyString`            | `""`                          | `""`             | Empty string                 |

### `testTrimLeadingZeros` - tests trimLeadingZeros()

| Test Case Name                        | Input        | Expected | Description            |
| ------------------------------------- | ------------ | -------- | ---------------------- |
| `testTrimLeadingZeros_oneZero`        | `"0123"`     | `"123"`  | One leading zero       |
| `testTrimLeadingZeros_severalZeros`   | `"00000123"` | `"123"`  | Multiple leading zeros |
| `testTrimLeadingZeros_noZeros`        | `"123"`      | `"123"`  | No leading zeros       |
| `testTrimLeadingZeros_zeroOnEnd`      | `"1230"`     | `"123"`  | Zero at the end        |
| `testTrimLeadingZeros_zeroAfterSpace` | `" 0123"`    | `"123"`  | Zero after space       |
| `testTrimLeadingZeros_emptyString`    | `""`         | `""`     | Empty string           |

### `testConvertErrorToCrash` - tests convertErrorToCrash()

| Test Case Name                         | Input          | Expected               | Description                |
| -------------------------------------- | -------------- | ---------------------- | -------------------------- |
| `testConvertErrorToCrash_SUUCESS`      | `SUCCESS`      | `RUNNING`              | SUCCESS error code         |
| `testConvertErrorToCrash_BAD_ARGUMENT` | `BAR_ARGUMENT` | `MODULE_BAD_ARGUMENT`  | BAD_ARGUMENT error code    |
| `testConvertErrorToCrash_MALLOC_ERROR` | `MALLOC_ERROR` | `MODULE_MALLOC_ERROR`  | MALLOC_ERROR code          |
| `testConvertErrorToCrash_invalid`      | `34`           | `MODULE_INVALID_ERROR` | Invalid enum cast          |
| `testConvertErrorToCrash_NULL`         | `NULL`         | `RUNNING`              | NULL pointer cast as error |

### `testFirstNullPointer` - tests firstNullPointer()

| Test Case Name                           | Input                        | Expected   | Description          |
| ---------------------------------------- | ---------------------------- | ---------- | -------------------- |
| `testFirstNullPointer_nullPointerInside` | `{123, 456, 789, NULL, 321}` | `3`        | NULL inside array    |
| `testFirstNullPointer_firstNullPointer`  | `{NULL, 123, 456, 789, 321}` | `0`        | NULL at index 0      |
| `testFirstNullPointer_lastNullPointer`   | `{123, 456, 789, 321, NULL}` | `4`        | NULL at last index   |
| `testFirstNullPointer_noNullPointer`     | `{123, 456, 789, 987, 321}`  | `5` (size) | No NULL in array     |
| `testFirstNullPointer_arrayNullr`        | `NULL`                       | `0`        | Array itself is NULL |
