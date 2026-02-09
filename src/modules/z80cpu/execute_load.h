#ifndef EXEC_LOAD
#define EXEC_LOAD

#include "z80cpuMod.h"

enum Error ld_r_rp(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_r_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_r_n(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_$hl$_r(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_$bc$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_$de$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_$nn$(struct Instance* __restrict i, void** __restrict inf);

#endif
