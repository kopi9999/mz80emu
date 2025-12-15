add_library(testUiMod SHARED test/testUiMod.cpp uiModuleFunctions.cpp)

if(WIN32)
    target_link_libraries(testUiMod PRIVATE wx::core wx::base)
elseif(UNIX)
    target_link_libraries(testUiMod PRIVATE ${wxWidgets_LIBRARIES})
endif()
