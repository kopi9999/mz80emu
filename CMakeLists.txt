cmake_minimum_required(VERSION 3.10)
project(mz80emu)
add_library(test SHARED src/testdll.c)
add_executable(mz80emu src/main.cpp src/test.c src/loadlib.c)
