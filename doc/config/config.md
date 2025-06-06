# config.txt

`config.txt` file contains data about modules, their instances, interfaces and clock, which will be loaded and used to run them when the emulator starts.  


## File structure

Data stored in the file is organized into sections marked with headers. Header row have to start with an appropriate text defining start of section, but it can also contain another characters (which are ignored by the program). For example, user can add a colon after header in order to improve legibility. All headers are given below, in "Sections" section.  
Under the header is located data loaded and used by the emulator. Usually, one row includes only one information, but it depends on the section. Sometimes several elements separated by a space are in a row. The config file accepts various whitespace characters to separate elements, including spaces and tabs. Multiple whitespace characters between two elements are also acceptable. In the section can be located only necessary data and empty rows, which are ignored.  
An order of the sections is not fixed, so user is not obliged to follow it. It is even possible to divide a section into many parts by creating several sections with the same header - all of them will be loaded correctly.


## Sections

All information in the section should be in separate rows, unless otherwise stated in the section description. For values referring to elements from another section, a value 0 refers to the first element of that section, value 1 to the second, and so on.

### `Modules`
`Modules` section contains names of modules which will be able to be used to create module instances. Because all modules are DLL libraries, their names should end with `.dll` extension.

### `Module instances`
This section defines module instances which will be created when the emulator starts. Each instance is marked with a number which refers to the name in `Modules` section.

### `Interfaces`
Describes an interfaces which will be created basing on the module instances. Each number in this section indicates one element from `Module instances` section.

### `Derived interfaces`
Section with a bit more complex syntax of elements, which describe derived interfaces. Every derived interface should be marked with word `new`. Next, in another rows is located information about sub-elements of that derived interface. In each row should be two numbers divided with space. First of them refers to interface in `Interfaces` section, second indicates to its sub-element. Derived interface will comprise all indicated sub-elements.

### `Clock period`
`Clock period` section specifies only one value - time between successive clock ticks in nanoseconds. If more than one number is given in the section, the last of them will be loaded.

### `Clock depth`
`Clock depth` also defines one value - number of clock states. Similarly to the case of previous section, only the last value will be taken into account when more than one number is given.

### `Strobe up instances`
Section defining order of calling `strobeUp()` function of module instances. First instance in this section will be handled first. All numbers representing instances indicate elements of `Module instances` section.

### `Strobe up interfaces`
Describes which interfaces will be passed to the `strobeUp()` function of module instances. Elements refer to `Interfaces` section. These elements are related to the ones in `Strobe up instances` section - when the instance in `Strobe up instances` is being handled, to its `strobeUp()` function is passed the interface in `Strobe up interfaces`.

### `Strobe up clock`
Specifies on which clock states the `strobeUp()` function of module instances will be called. Elements in this section are related to elements in `Strobe up instances` section - each row represents one instance. Number of values in a row should be equal to the number of clock states. These values have to be divided with spaces. Acceptable values are `true` and `false` (letter case does not matter). `True` means that `strobeUp()` will be called on specific clock state, while `false` means the opposite.

### `Strobe down instances`
See `Strobe up instances` - referring to `strobeDown()` instead of `strobeUp()`.

### `Strobe down interfaces`
See `Strobe up interfaces` - referring to `strobeDown()` instead of `strobeUp()`.

### `Strobe down clock`
See `Strobe up clock` - referring to `strobeDown()` instead of `strobeUp()`.


## Example structure of file

```
Modules:
test.dll

Module instances:
0
0

Interfaces:
0
1

Derived interfaces:
new
0 0
1 0

Clock period:
250000000

Clock depth:
2

Strobe up instances:
0
1

Strobe up interfaces:
0
0

Strobe up clock:
true false
false true

Strobe down instances:
0
1

Strobe down interfaces:
0
0

Strobe down clock:
false true
true false
```