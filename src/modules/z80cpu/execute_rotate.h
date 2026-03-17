#ifndef EXEC_ROTATE
#define EXEC_ROTATE

#include "z80cpuMod.h"

enum Error rlca(struct Instance* __restrict i, void** __restrict inf);
enum Error rla(struct Instance* __restrict i, void** __restrict inf);
enum Error rra(struct Instance* __restrict i, void** __restrict inf);
enum Error rlc_r(struct Instance* __restrict i, void** __restrict inf);
enum Error rlc_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error rl_r(struct Instance* __restrict i, void** __restrict inf);
enum Error rl_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error rrc_r(struct Instance* __restrict i, void** __restrict inf);
enum Error rrc_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error rr_r(struct Instance* __restrict i, void** __restrict inf);
enum Error rr_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error sla_r(struct Instance* __restrict i, void** __restrict inf);
enum Error sla_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error sra_r(struct Instance* __restrict i, void** __restrict inf);
enum Error sra_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error srl_r(struct Instance* __restrict i, void** __restrict inf);
enum Error srl_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error rld(struct Instance* __restrict i, void** __restrict inf);
enum Error rrd(struct Instance* __restrict i, void** __restrict inf);

#endif
