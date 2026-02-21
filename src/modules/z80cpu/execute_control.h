#ifndef EXEC_CONTROL
#define EXEC_CONTROL

#include "z80cpuMod.h"

enum Error halt(struct Instance* __restrict i, void** __restrict inf);
enum Error nop(struct Instance* __restrict i, void** __restrict inf);
enum Error daa(struct Instance* __restrict i, void** __restrict inf);

#endif
