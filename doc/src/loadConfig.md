# loadConfig.cpp

`loadConfig.cpp` file is responsible for loading and validating data from `config.txt` file. This data can then be used in program, for example to initialization.

## Overview

The file contains one main function named `loadConfig`. It uses other functions in the file in appropriate way to load data from configuration file and returns it by pointers provided as function arguments.

At the beginning the function checks if `config.txt` file exists. Then, it loads data from this file line by line. Simultaneously, there is performed a first part of validation. Each line is validated instantly after loading. When the line is invalid, loading is canceled. First part of validation detects such errors as passing a text when a number is expected or incorrect number of values.

Data immediately after loading and initial validation is still not suitable for use. So next begins a second part of validation and parallel loading data to appropriate pointers. This part of validation can detect errors impossible to find before the enitre data is loaded. They include, among others: an ID which does not exist or situation when number of values in corresponding sections is not equal. This part is also performed "line by line" - program validates one part of data and if it is valid, it is loaded to pointer with data ready to use.

When the configuration file cannot be found or its structure is invalid, the function returns an error code from `CrashCode` enumerator. When all operations have been processed correctly, it returns `RUNNING` code.