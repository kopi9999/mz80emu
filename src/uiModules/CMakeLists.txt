add_library(testUiMod SHARED test/testUiMod.cpp uiModuleFunctions.cpp)

if(WIN32)
    target_link_libraries(testUiMod wx::core wx::base)
elseif(UNIX)
    target_link_libraries(testUiMod ${wxWidgets_LIBRARIES})
endif()
