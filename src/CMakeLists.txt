add_library(config SHARED config.cpp validation.cpp misc.cpp)

add_executable(mz80emu main.cpp loadlib.c misc.c misc.cpp validation.cpp init.cpp)
target_link_libraries(mz80emu PRIVATE config)
