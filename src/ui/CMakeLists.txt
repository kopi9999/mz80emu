add_executable(configurator ConfiguratorFrame.cpp App.cpp)
add_executable(memmod memory_module/MemoryModule.cpp)
if(WIN32)
    target_link_libraries(configurator wx::core wx::base)
    target_link_libraries(memmod wx::core wx::base)
elseif(UNIX)
    target_link_libraries(configurator ${wxWidgets_LIBRARIES})
    target_link_libraries(memmod ${wxWidgets_LIBRARIES})
endif()


