cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

project(mz80emu)
add_library(testMod SHARED src/modules/test/testdll.c)
add_library(config SHARED src/loadConfig.cpp src/validation.cpp src/misc.cpp)

add_executable(mz80emu src/main.cpp src/loadlib.c src/misc.c src/misc.cpp src/validation.cpp src/init.cpp)
target_link_libraries(mz80emu PRIVATE config)

include_directories(boost)
link_directories(boost/stage/lib)

add_executable(test_mz80emu src/unitTests/misc.cpp src/unitTests/validation.cpp src/misc.cpp src/validation.cpp )
add_executable(test_testDll src/modules/test/testdll.c src/modules/test/unitTests/test.cpp)

include(Ctest)
add_test(NAME test_mz80emu COMMAND test_mz80emu --report_level=detailed)
add_test(NAME test_testDll COMMAND test_testDll --report_level=detailed)
