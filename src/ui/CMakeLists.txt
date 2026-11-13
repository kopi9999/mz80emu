###
## SPDX_License_identifier: GPL-3.0-or-later
## Copyright (c) 2026 kopi9999
## This file is a part of mz80emu project.
#

add_executable(configurator ConfiguratorFrame.cpp App.cpp)
if(WIN32)
    target_link_libraries(configurator wx::core wx::base)
elseif(UNIX)
    target_link_libraries(configurator ${wxWidgets_LIBRARIES})
endif()


