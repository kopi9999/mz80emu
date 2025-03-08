# main.cpp

`main.cpp` file is responsible for running emulator by initialization of all necessary modules and supervising clock. It contains:
- variables storing data of modules, instances and interfaces,
- defintions of types used to storing pointers to functions in arrays,
- definition of struct containing modules data.

## Structs

### `Modules`
`Modules` is struct used to create `modules` variable storing all data concerning modules (not to be confused with module instances). Its fields includes:
- `names` - vector of all modules names (with added .dll extension), so that it can be used to recognise specific module DLL libraries.
- `count` - number of modules.
- `pointers` - array of pointers to loaded DLL libraries.
- `createFuncs`, `createInterfacesFuncs`, `strobeUpFuncs`, `strobeDownFuncs`, `destroyFuncs`, `destroyInterfacesFuncs` - arrays of pointers to modules functions having names corresponding to names of these arrays.

In case of arrays and vectors, values at a given index in all of them correspond to the same specific module.

## Functions

### `main()`
**Returns: int** (a number greater than 0 if an error occurs before the main loop starts, 0 in other cases)

`main()` function takes care of loading essential data, correct processing it and running main loop.

At first, function loads data from configuration files and saves it in proper variables and arrays. Next, loads all modules DLL libraries and creates pointers to their functions, saving them in `modules` struct. For this purpose it uses `loadLibs()` and `loadModuleFunctions()`.

When loading is completed, program creates instances of modules and interfaces basing on data taken from configuration files. To store them, there are used `instances`, `interfaces` and `interfacesElements` arrays.

Then, variables used to simulate clock are created. They consists of `clockState` (storing current clock state), `start`, `end` and `duration` variables used for changing clock state at proper time with `chrono::high_resolution_clock`.

Finally, a main loop starts. In each iteration it calls `strobeUp()` and `strobeDown()` functions of all module instances. Next, program waits for the appropriate amount of time and increments `clockState` variable or changes its value to zero in case when it is equal to `clockDepth`, meaning number of clock states.

If an error occurs when program tries to load module, get pointer to module function, create module instance or interface, or any of `strobeUp()` and `strobeDown()` functions returns error, all libraries are unloaded with `unloadLibs()` function and `main()` stops.

### `loadLibs(libs, libNames, libCount)`
**Returns: bool** (true when error occurs, otherwise false)

**Parameters:**
- **void\*\* libs** - array to be filled with pointers to DLL libraries.
- **vector\<string> libNames** - vector including names of libraries to load.
- **uint16_t libCount** - number of libraries to be loaded.

`loadLibs()` loads DLL libraries and saves pointers to them in an array provided as an argument. Index of value to which pointer is to be loaded corresponds to index of library name in provided array. When library with specific name does not exist, function shows proper information in console and returns true. It also displays informations about successfully loaded libraries.

### `loadModuleFunctions()`
**Returns: bool** (true when functions are loaded successfully, otherwise false)

`loadModuleFunctions()` saves pointers to the modules functions in proper arrays in `modules` variable. Loaded functions comprises: `create`, `createInterfaces`, `strobeUp`, `strobeDown`, `destroy` and `destroyInterfaces`. When a module function cannot be loaded, proper information is printed to the console and `loadModuleFunctions()` returns false. It also displays information when all module functions are loaded successfully.