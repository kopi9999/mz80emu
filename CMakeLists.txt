cmake_minimum_required(VERSION 3.24)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:$(CMAKE_SOURCE_DIR)>)
endif()

project(mz80emu)

if(WIN32)
    set(wxBUILD_SHARED OFF)
    add_subdirectory(wxWidgets) # building static wxWidgets from source on windows

    if(EXISTS boost/)
        include_directories(boost) # local boost.test headers
        set(Boost_FOUND True)
    else()
        set(Boost_FOUND False)
    endif()
elseif(UNIX) 
    find_package(wxWidgets REQUIRED COMPONENTS core base) # using prebuilt dynamic wxWidgets for unix-like
    if(wxWidgets_USE_FILE)
        include(${wxWidgets_USE_FILE})
    endif()
    
    find_package(Boost NO_MODULE) # global boost.test headers
endif()

add_subdirectory(src build) # main emulator
add_subdirectory(src/modules build/modules) # modules
add_subdirectory(src/ui build/ui) # ui
if(Boost_FOUND)
    add_subdirectory(src/unitTests build/unitTests) # unit tests
endif()

