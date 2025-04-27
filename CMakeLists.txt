cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

project(mz80emu)
add_library(test SHARED src/modules/test/testdll.c)
add_executable(mz80emu src/main.cpp src/loadlib.c src/misc.c)

set(wxBUILD_SHARED OFF)

add_subdirectory(wxWidgets)
add_executable(emulator_ui src/ui/MainFrame.cpp src/ui/App.cpp src/ui/FileOperations.cpp)
target_link_libraries(emulator_ui wx::net wx::core wx::base)