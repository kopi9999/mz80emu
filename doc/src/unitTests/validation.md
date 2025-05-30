## `testStringIsInteger`

| Test Case Name                                | Input          | Expected | Description                             |
| --------------------------------------------- | -------------- | -------- | --------------------------------------- |
| `testStringIsInteger_emptyString`             | `""`           | `false`  | Empty string should not be accepted.    |
| `testStringIsInteger_singleDigit`             | `"2"`          | `true`   | Single digit is valid.                  |
| `testStringIsInteger_multiDigit`              | `"242"`        | `true`   | Multi-digit value is valid.             |
| `testStringIsInteger_everyDigit`              | `"1234567890"` | `true`   | All digits accepted.                    |
| `testStringIsInteger_zeroFirst`               | `"02"`         | `true`   | Leading zero is accepted.               |
| `testStringIsInteger_alphabetic`              | `"Test"`       | `false`  | Alphabetic input is invalid.            |
| `testStringIsInteger_alphanumericNumberFirst` | `"1Test"`      | `false`  | Digits followed by letters are invalid. |
| `testStringIsInteger_alphanumericNumberLast`  | `"Test1"`      | `false`  | Letters followed by digits are invalid. |
| `testStringIsInteger_alphanumericZeroInside`  | `"Tes1t"`      | `false`  | Alphanumeric in middle is invalid.      |
| `testStringIsInteger_space`                   | `" "`          | `false`  | Whitespace is not a number.             |

## `testStringIsBool`

| Test Case Name                 | Input            | Expected | Description                  |
| ------------------------------ | ---------------- | -------- | ---------------------------- |
| `testStringIsBool_true`        | `"true"`         | `true`   | Valid boolean.               |
| `testStringIsBool_True`        | `"True"`         | `true`   | Valid boolean (capitalized). |
| `testStringIsBool_TRUE`        | `"TRUE"`         | `true`   | Valid boolean (uppercase).   |
| `testStringIsBool_false`       | `"false"`        | `true`   | Valid boolean.               |
| `testStringIsBool_False`       | `"False"`        | `true`   | Valid boolean (capitalized). |
| `testStringIsBool_FALSE`       | `"FALSE"`        | `true`   | Valid boolean (uppercase).   |
| `testStringIsBool_helloWorld`  | `"Hello World!"` | `false`  | Invalid boolean string.      |
| `testStringIsBool_tabulator`   | `"\t"`           | `false`  | Tab character is invalid.    |
| `testStringIsBool_emptyString` | `""`             | `false`  | Empty input is invalid.      |

## `testVectorSize`

| Test Case Name                             | Input                           | Expected | Description                |
| ------------------------------------------ | ------------------------------- | -------- | -------------------------- |
| `testVectorSize_empty_goodValue`           | `{}`, `0`                       | `true`   | Correct empty vector size. |
| `testVectorSize_empty_badValue`            | `{}`, `6`                       | `false`  | Too few elements.          |
| `testVectorSize_singleElement_goodValue`   | `{"test"}`,  `1`                | `true`   | Exact match.               |
| `testVectorSize_singleElement_lowerValue`  | `{"test"}`, `0`                 | `false`  | Too many elements.         |
| `testVectorSize_singleElement_higherValue` | `{"test"}`, `5`                 | `false`  | Too few elements.          |
| `testVectorSize_multiElement_goodValue`    | `{"test", "test", "test"}`, `3` | `true`   | Exact match.               |
| `testVectorSize_multiElement_lowerValue`   | `{"test", "test", "test"}`, `0` | `false`  | Too many elements.         |
| `testVectorSize_multiElement_higherValue`  | `{"test", "test", "test"}`, `5` | `false`  | Too few elements.          |

## `testDerivedInterfaceCreated`

| Test Case Name                             | Input        | Expected | Description                                     |
| ------------------------------------------ | ------------ | -------- | ----------------------------------------------- |
| `testDerivedInterfacesCreated_properTable` | 2x2x2 vector | `true`   | Valid nested structure.                         |
| `testDerivedInterfacesCreated_emptyTable`  | `{}`         | `false`  | No interface created but values were specified. |

## `testDerivedInterfaceHasValues`

| Test Case Name                              | Input      | Expected | Description                                      |
| ------------------------------------------- | ---------- | -------- | ------------------------------------------------ |
| `testDerivedInterfaceHasValues_properTable` | 2x2 vector | `true`   | Valid interface values.                          |
| `testDerivedInterfaceHasValues_emptyTable`  | `{}`       | `false`  | Interface created, but no values were specified. |

## `testIdExist`

| Test Case Name               | ID        | Expected | Description                  |
| ---------------------------- | --------- | -------- | ---------------------------- |
| `testIdExist_lowerThanMax`   | `3`, `5`  | `true`   | ID exists (within range).    |
| `testIdExist_exualToMax`     | `5`, `5`  | `true`   | ID equals max ID (boundary). |
| `testIdExist_greaterThanMax` | `10`, `5` | `false`  | ID is out of range.          |

## `testValueDoesNotEqualZero`

| Test Case Name                             | Value | Expected | Description                 |
| ------------------------------------------ | ----- | -------- | --------------------------- |
| `testValueDoesNotEqualZero_notEqualToZero` | `5`   | `true`   | Valid non-zero input.       |
| `testValueDoesNotEqualZero_equalToZero`    | `0`   | `false`  | Zero is considered invalid. |

## `testValueEqualsNumberOfInstances`

| Test Case Name                              | Value    | Expected | Description                           |
| ------------------------------------------- | -------- | -------- | ------------------------------------- |
| `testValueEqualsNumberOfInstances_equal`    | `5`, `5` | `true`   | Match between value and instances.    |
| `testValueEqualsNumberOfInstances_notEqual` | `5`, `1` | `false`  | Mismatch between value and instances. |

## `testVectorHasUniqueValues`

| Test Case Name                                            | Input                | Expected | Description                   |
| --------------------------------------------------------- | -------------------- | -------- | ----------------------------- |
| `testVectorHasUniqueValues_emptyVector`                   | `{}`                 | `true`   | No duplicates possible.       |
| `testVectorHasUniqueValues_singleElement`                 | `{"test"}`           | `true`   | One element is always unique. |
| `testVectorHasUniqueValues_doubleElement_equal`           | `{"test", "test"}`   | `false`  | Duplicate detected.           |
| `testVectorHasUniqueValues_doubleElement_unique`          | `{"testA", "testB"}` | `true`   | All elements are unique.      |
| `testVectorHasUniqueValues_doubleElement_equal_zeroFirst` | `{"00test", "test"}` | `false`  | Interpreted as not unique.    |
