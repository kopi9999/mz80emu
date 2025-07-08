add_executable(test_mz80emu misc.cpp validation.cpp ../misc.cpp ../validation.cpp)
add_executable(test_testMod ../modules/test/testMod.c ../modules/test/unitTests/test.cpp)

add_test(NAME test_mz80emu COMMAND test_mz80emu --report_level=detailed)
add_test(NAME test_testMod COMMAND test_testMod --report_level=detailed)
