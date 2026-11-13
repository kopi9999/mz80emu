/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef MODULE_INTERNAL
#define MODULE_INTERNAL

#ifdef _WIN32
    #include "uiModuleWindows.hpp"
#else
    #include "uiModule.hpp"
#endif

extern const char* moduleName;
extern const char* moduleDescription;
extern const uint16_t moduleMajorVersion;
extern const uint16_t moduleMinorVersion;
extern const uint16_t protocolVersion;

#endif
