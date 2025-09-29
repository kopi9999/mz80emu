add_executable(test_mz80emu misc.cpp validation.cpp ../misc.cpp ../validation.cpp)
add_executable(test_moduleFunctions ../modules/test_moduleFunctions.cpp ../modules/moduleFunctions.c)
add_executable(test_testMod ../modules/test/testMod.c ../modules/test/unitTests/test.cpp)
add_executable(test_memoryMod ../modules/memory/memoryMod.c ../modules/memory/unitTests/test.cpp)

add_test(NAME test_mz80emu COMMAND test_mz80emu --report_level=detailed)
add_test(NAME test_moduleFunctions COMMAND test_moduleFunctions --report_level=detailed)
add_test(NAME test_testMod COMMAND test_testMod --report_level=detailed)
add_test(NAME test_memoryMod COMMAND test_memoryMod --report_level=detailed)
