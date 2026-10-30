/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef LOADLIB
#define LOADLIB
#include <stdint.h>

extern void* loadLib(const char*);
extern bool loadFuncs(void**, void**, uint16_t, const char*);
extern void* loadFunc(void*, const char*);
extern bool unloadLib(void*);
extern bool unloadLibs(void**, uint16_t);
extern char* getError();

#endif
