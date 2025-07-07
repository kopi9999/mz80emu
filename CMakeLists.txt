cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:$(CMAKE_SOURCE_DIR)>)

project(mz80emu)

include(Ctest) # for unit test report
include_directories(boost) # unit testing library
if(WIN32) # building static wxWidgets from source on windows
    set(wxBUILD_SHARED OFF)
    add_subdirectory(wxWidgets)
endif()
if(UNIX) # using prebuilt dynamic wxWidgets for unix-like
    find_package(wxWidgets REQUIRED COMPONENTS core base)
endif()

add_subdirectory(src build) # main emulator
add_subdirectory(src/modules build/modules) # modules
add_subdirectory(src/ui build/ui) # ui
add_subdirectory(src/unitTests build/unitTests) # unit tests

