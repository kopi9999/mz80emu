/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef DECODE
#define DECODE

#include "z80cpuMod.h"

enum Instruction decodeInstruction(struct Instance* __restrict i);
enum Instruction decodeInstruction_CB (struct Instance* __restrict i);
enum Instruction decodeInstruction_ED (struct Instance* __restrict i);

#endif
