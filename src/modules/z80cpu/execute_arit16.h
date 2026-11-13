/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef EXEC_ARIT16
#define EXEC_ARIT16

#include "z80cpuMod.h"

enum Error add_hl_ss(struct Instance* __restrict i, void** __restrict inf);
enum Error adc_hl_ss(struct Instance* __restrict i, void** __restrict inf);
enum Error sbc_hl_ss(struct Instance* __restrict i, void** __restrict inf);
enum Error inc_ss(struct Instance* __restrict i, void** __restrict inf);
enum Error dec_ss(struct Instance* __restrict i, void** __restrict inf);

#endif
