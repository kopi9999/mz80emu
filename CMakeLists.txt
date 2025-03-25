cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

project(mz80emu)
add_library(test SHARED src/modules/test/testdll.c)
add_executable(testTestDll src/modules/test/testdll.c src/modules/test/unitTests/main.c)

add_executable(mz80emu src/main.cpp src/loadlib.c src/misc.c)
