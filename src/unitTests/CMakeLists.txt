add_executable(test_mz80emu misc.cpp validation.cpp ../misc.cpp ../validation.cpp)
add_executable(test_testDll ../modules/test/testdll.c ../modules/test/unitTests/test.cpp)

add_test(NAME test_mz80emu COMMAND test_mz80emu --report_level=detailed)
add_test(NAME test_testDll COMMAND test_testDll --report_level=detailed)
