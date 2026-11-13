/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef EXEC_BIT_SET_RESET
#define EXEC_BIT_SET_RESET

#include "z80cpuMod.h"

enum Error bit_b_r(struct Instance *__restrict i, void **__restrict inf);
enum Error bit_b_$hl$(struct Instance *__restrict i, void **__restrict inf);
enum Error set_b_r(struct Instance *__restrict i, void **__restrict inf);
enum Error set_b_$hl$(struct Instance *__restrict i, void **__restrict inf);
enum Error res_b_r(struct Instance *__restrict i, void **__restrict inf);
enum Error res_b_$hl$(struct Instance *__restrict i, void **__restrict inf);

#endif
