cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:$(CMAKE_SOURCE_DIR)>)

project(mz80emu)

add_subdirectory(src build)

set(wxBUILD_SHARED OFF)

add_subdirectory(wxWidgets)
add_subdirectory(src/ui build/ui)

include_directories(boost)
link_directories(boost/stage/lib)

include(Ctest)
add_subdirectory(src/modules build/modules)
add_subdirectory(src/unitTests build/unitTests)
