cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:$(CMAKE_SOURCE_DIR)>)
endif()

project(mz80emu)

if(WIN32) # building static wxWidgets from source on windows
    set(wxBUILD_SHARED OFF)
    add_subdirectory(wxWidgets)
    include_directories(boost) # unit testing library
endif()
if(UNIX) # using prebuilt dynamic wxWidgets for unix-like
    find_package(wxWidgets REQUIRED COMPONENTS core base)
    if(wxWidgets_USE_FILE)
        include(${wxWidgets_USE_FILE})
    endif()
    find_package(Boost NO_MODULE)
endif()

add_subdirectory(src build) # main emulator
add_subdirectory(src/modules build/modules) # modules
add_subdirectory(src/ui build/ui) # ui
add_subdirectory(src/unitTests build/unitTests) # unit tests

