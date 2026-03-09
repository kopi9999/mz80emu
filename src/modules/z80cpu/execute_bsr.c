#include "execute_bsr.h"
#include "execute_control.h"

enum Error bit_b_r(struct Instance* __restrict i, void** __restrict inf){
  i->F |= (0b10000000 & i->A) >> 7;
  i->A = i->A << 1;
  i->A |= i->F & 0b0000001;

  i->F &= 0b11101101;
  return nop(i, inf);
}
