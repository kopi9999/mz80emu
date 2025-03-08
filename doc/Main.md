# main.cpp

`main.cpp` file is responsible for running emulator by initialization of all necessary modules and supervising clock. It contains:
- variables storing data of module instances and interfaces,
- defintions of types used to storing pointers to functions in arrays,
- definition of struct containing modules data.

## Structs

### `Modules`
`Modules` is struct used to create `modules` variable storing all data concerning modules (not to be confused with module instances). Its fields includes:
- `names` - 
- `count` - 
- `pointers` - 
- `createFuncs` - 
- `createInterfacesFuncs` - 
- `strobeUpFuncs` - 
- `strobeDownFuncs` - 
- `destroyFuncs` - 
- `destroyInterfacesFuncs` - 

## Functions

### `main()`
`main()` function takes care of loading essential data, correct processing it and running main loop.

At first, function loads data from configuration files and saves it in proper variables and arrays. Next, loads all modules dll libraries and creates pointers to their functions, saving them in `modules` struct. For this purpose it uses `loadLibs()` and `loadModuleFunctions()`.

When loading is completed, program creates instances of modules and interfaces basing on data taken from configuration files. To store them, there are used `instances`, `interfaces` and `interfacesElements` arrays.

Then, variables used to simulate clock are created. They consists of `clockState` (storing current clock state), `start`, `end` and `duration` variables used for changing clock state at proper time with `chrono::high_resolution_clock`.

Finally, a main loop starts. In each iteration it calls `strobeUp()` and `strobeDown()` functions of all module instances. Next, program waits for the appropriate amount of time and increments `clockState` variable or changes its value to zero in case when it was equal to `clockDepth`, meaning the last clock state.

If an error occurs when program tries to load module, get pointer to module function, create module instance or interface, or any of `strobeUp()` and `strobeDown()` functions returns error, all libraries are unloaded with `unloadLibs()` function and `main()` stops.