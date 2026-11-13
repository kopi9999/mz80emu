/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef M_OPERATIONS
#define M_OPERATIONS

#include "z80cpuMod.h"

extern enum Error m1_strobeUp(struct Instance* instance, void** interfaces);
extern enum Error m1_strobeDown(struct Instance* instance, void** interfaces);
extern enum Error m2_strobeUp(struct Instance* instance, void** interfaces);
extern enum Error m2_strobeDown(struct Instance* instance, void** interfaces);
extern enum Error m3_strobeUp(struct Instance* instance, void** interfaces);
extern enum Error m3_strobeDown(struct Instance* instance, void** interfaces);

#endif
