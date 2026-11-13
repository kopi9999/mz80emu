/*
 * SPDX_License_identifier: GPL-3.0-or-later
 * Copyright (c) 2026 kopi9999
 * This file is a part of mz80emu project.
 */

#ifndef EXEC_EXCHANGE
#define EXEC_EXCHANGE

#include "z80cpuMod.h"

enum Error ex_de_hl(struct Instance* __restrict i, void** __restrict inf);
enum Error ex_af_af(struct Instance* __restrict i, void** __restrict inf);
enum Error exx(struct Instance* __restrict i, void** __restrict inf);
enum Error ex_$sp$_hl(struct Instance* __restrict i, void** __restrict inf);
enum Error ldi(struct Instance* __restrict i, void** __restrict inf);
enum Error ldir(struct Instance* __restrict i, void** __restrict inf);
enum Error ldd(struct Instance* __restrict i, void** __restrict inf);
enum Error lddr(struct Instance* __restrict i, void** __restrict inf);
enum Error cpi(struct Instance* __restrict i, void** __restrict inf);
enum Error cpir(struct Instance* __restrict i, void** __restrict inf);
enum Error cpd(struct Instance* __restrict i, void** __restrict inf);
enum Error cpdr(struct Instance* __restrict i, void** __restrict inf);

#endif
