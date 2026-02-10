add_library(testMod SHARED test/testMod.c moduleFunctions.c)
add_library(memoryMod SHARED memory/memoryMod.c moduleFunctions.c)
add_library(z80cpuMod SHARED z80cpu/z80cpuMod.c z80cpu/mOperations.c z80cpu/decode.c z80cpu/execute.c z80cpu/execute_control.c z80cpu/execute_load.c z80cpu/execute_jump.c z80cpu/execute_arit.c moduleFunctions.c)
