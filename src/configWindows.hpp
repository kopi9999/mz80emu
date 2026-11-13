/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 Daw151
 * This file is a part of mz80emu project.
 */

#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include "main.hpp"

__declspec(dllexport) enum CrashCode loadConfig(struct Modules*, struct InstanceInfo*, struct InterfacesInfo*, struct ClockInfo*);
__declspec(dllexport) enum CrashCode rawDataToFile(std::vector<std::string>, std::vector<std::string>, struct RawInterfacesInfo, struct RawClockInfo);

#endif
