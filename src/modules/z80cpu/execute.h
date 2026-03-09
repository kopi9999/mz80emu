#ifndef EXEC
#define EXEC

#include "z80cpuMod.h"

enum Error execute_up(struct Instance* __restrict i, void** __restrict inf);
enum Error execute_down(struct Instance* __restrict i, void** __restrict inf);

#endif
