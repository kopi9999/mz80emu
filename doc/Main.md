# main.cpp

`main.cpp` file is responsible for running emulator by initialization of all necessary modules and supervising clock. It contains:
- variables storing data of module instances and interfaces,
- defintions of types used to storing pointers to functions in arrays,
- definition of struct containing modules data.

## Structs

## Functions

### `main()`
`main()` function is run when program starts and works until end.  
At first, `main()` loads data from configuration files and saves it in proper variables and arrays. Next, loads all modules dll libraries and creates pointers to their functions, saving them in `modules` struct. For this purpose it uses `loadLibs()` and `loadModuleFunctions()`.