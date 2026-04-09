#ifndef EXEC_CALL
#define EXEC_CALL

#include "z80cpuMod.h"

enum Error call_nn(struct Instance* __restrict i, void** __restrict inf);
enum Error call_cc_nn(struct Instance* __restrict i, void** __restrict inf);
enum Error ret(struct Instance* __restrict i, void** __restrict inf);
enum Error ret_cc(struct Instance* __restrict i, void** __restrict inf);
enum Error rst_p(struct Instance* __restrict i, void** __restrict inf);

#endif
