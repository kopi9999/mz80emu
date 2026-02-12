#ifndef EXEC_ARIT
#define EXEC_ARIT

#include "z80cpuMod.h"

enum Error add_a_r(struct Instance* __restrict i, void** __restrict inf);
enum Error add_a_n(struct Instance* __restrict i, void** __restrict inf);

#endif
