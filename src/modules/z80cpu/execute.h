/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef EXEC
#define EXEC

#include "z80cpuMod.h"

enum Error execute_up(struct Instance* __restrict i, void** __restrict inf);
enum Error execute_down(struct Instance* __restrict i, void** __restrict inf);

#endif
