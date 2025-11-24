add_library(config SHARED config.cpp validation.cpp misc.cpp)

if(WIN32)
    add_executable(mz80emu main.cpp loadDLL.c misc.c misc.cpp validation.cpp init.cpp MainFrame.cpp)
    target_link_libraries(mz80emu wx::net wx::core wx::base config)
elseif(UNIX)
    add_executable(mz80emu main.cpp loadSO.c misc.c misc.cpp validation.cpp init.cpp MainFrame.cpp)
    target_link_libraries(mz80emu ${wxWidgets_LIBRARIES} config)
endif()
