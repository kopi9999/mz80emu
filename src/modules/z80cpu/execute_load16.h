#ifndef EXEC_LOAD16
#define EXEC_LOAD16

#include "z80cpuMod.h"

enum Error ld_dd_nn(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_hl_$nn$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_dd_$nn$(struct Instance* __restrict i, void** __restrict inf);

#endif
