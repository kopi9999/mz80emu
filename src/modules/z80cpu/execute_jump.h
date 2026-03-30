#ifndef EXEC_JUMP
#define EXEC_JUMP

#include "z80cpuMod.h"

enum Error jp_nn(struct Instance* __restrict i, void** __restrict inf);
enum Error jp_cc_nn(struct Instance* __restrict i, void** __restrict inf);
enum Error jr_e(struct Instance* __restrict i, void** __restrict inf);
enum Error jr_c_e(struct Instance* __restrict i, void** __restrict inf);
enum Error jr_nc_e(struct Instance* __restrict i, void** __restrict inf);
enum Error jr_z_e(struct Instance* __restrict i, void** __restrict inf);
enum Error jr_nz_e(struct Instance* __restrict i, void** __restrict inf);
enum Error jp_$hl$(struct Instance* __restrict i, void** __restrict inf);

#endif
