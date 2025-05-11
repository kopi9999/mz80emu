cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

project(mz80emu)
add_library(test SHARED src/modules/test/testdll.c)
add_library(testTestDll src/modules/test/testdll.c src/modules/test/unitTests/test.c)
add_library(testMisc src/unitTests/misc.cpp src/misc.cpp src/validation.cpp)
add_library(testInit src/unitTests/init.cpp src/init.cpp)

add_executable(unitTests src/unitTestSystem/unitTest.c)
target_link_libraries(unitTests PUBLIC testTestDll)
target_link_libraries(unitTests PUBLIC testMisc)
target_link_libraries(unitTests PUBLIC testInit)

add_executable(mz80emu src/main.cpp src/loadlib.c src/misc.c src/misc.cpp src/validation.cpp src/loadConfig.cpp src/init.cpp)
