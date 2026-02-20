#ifndef EXEC_ARIT
#define EXEC_ARIT

#include "z80cpuMod.h"

enum Error add_a_r(struct Instance* __restrict i, void** __restrict inf);
enum Error add_a_n(struct Instance* __restrict i, void** __restrict inf);
enum Error add_a_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error adc_a_r(struct Instance* __restrict i, void** __restrict inf);
enum Error adc_a_n(struct Instance* __restrict i, void** __restrict inf);
enum Error adc_a_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error sub_r(struct Instance* __restrict i, void** __restrict inf);
enum Error sub_n(struct Instance* __restrict i, void** __restrict inf);
enum Error sub_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error sbc_a_r(struct Instance* __restrict i, void** __restrict inf);
enum Error sbc_a_n(struct Instance* __restrict i, void** __restrict inf);
enum Error sbc_a_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error and_r(struct Instance* __restrict i, void** __restrict inf);
enum Error and_n(struct Instance* __restrict i, void** __restrict inf);
enum Error and_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error or_r(struct Instance* __restrict i, void** __restrict inf);
enum Error or_n(struct Instance* __restrict i, void** __restrict inf);
enum Error or_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error xor_r(struct Instance* __restrict i, void** __restrict inf);
enum Error xor_n(struct Instance* __restrict i, void** __restrict inf);
enum Error xor_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error cp_r(struct Instance* __restrict i, void** __restrict inf);
enum Error cp_n(struct Instance* __restrict i, void** __restrict inf);
enum Error cp_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error inc_r(struct Instance* __restrict i, void** __restrict inf);
enum Error inc_$hl$(struct Instance* __restrict i, void** __restrict inf);
enum Error dec_r(struct Instance* __restrict i, void** __restrict inf);
enum Error dec_$hl$(struct Instance* __restrict i, void** __restrict inf);
#endif
