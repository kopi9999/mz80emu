add_executable(configurator MainFrame.cpp App.cpp FileOperations.cpp)
target_link_libraries(configurator wx::net wx::core wx::base)
