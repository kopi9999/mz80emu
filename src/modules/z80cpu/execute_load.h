#ifndef EXEC_LOAD
#define EXEC_LOAD

#include "z80cpuMod.h"

enum Error ld_r_rp(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_r_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_r_n(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_$hl$_r(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_$hl$_n(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_$bc$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_$de$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_$nn$(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_$bc$_a(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_$de$_a(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_$nn$_a(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_i(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_a_r(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_i_a(struct Instance* __restrict i, void** __restrict inf);
enum Error ld_r_a(struct Instance* __restrict i, void** __restrict inf);

#endif
