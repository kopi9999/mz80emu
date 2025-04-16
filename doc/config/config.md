# config.txt

`config.txt` file contains data about modules, their instances, interfaces and clock, which will be loaded and used to run them when the emulator starts.  

## File structure

Data stored in the file is arranged in the sections marked by headers. Header row have to start with an appropriate text defining start of section, but it can also contain another characters (which are ignored by the program). For example, user can add a colon after header in order to improve legibility. All headers are given below, in "Sections" section.  
Under the header is located data loaded and used by the emulator. Usually, one row includes only one information, but it depends on the section. Sometimes several informations divided by single spaces are in a row. Anyway, in the section can be located only necessary data and empty rows, which are ignored.  
An order of the sections is not fixed, so user is not obliged to follow it. It is even possible to divide a section into many parts by creating several sections with the same header - all of them would be loaded correctly.

## Sections

### Modules

### Module instances

### Interfaces

### Derived interfaces

### Clock period

### Clock depth

### Strobe up instances

### Strobe up interfaces

### Strobe up clock

### Strobe down instances

### Strobe down interfaces

### Strobe down clock

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