#ifndef EXEC_ROTATE
#define EXEC_ROTATE

#include "z80cpuMod.h"

enum Error rlca(struct Instance* __restrict i, void** __restrict inf);
enum Error rla(struct Instance* __restrict i, void** __restrict inf);
enum Error rra(struct Instance* __restrict i, void** __restrict inf);

#endif
