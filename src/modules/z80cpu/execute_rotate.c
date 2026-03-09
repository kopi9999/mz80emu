#include "execute_rotate.h"
#include "execute_control.h"

enum Error rlca(struct Instance* __restrict i, void** __restrict inf){
  i->F |= (0b10000000 & i->A) >> 7;
  i->A = i->A << 1;
  i->A |= i->F & 0b0000001;

  i->F &= 0b11101101;
  return nop(i, inf);
}

enum Error rla(struct Instance* __restrict i, void** __restrict inf){
  uint8_t carry = (0b10000000 & i->A) >> 7;
  i->A = i->A << 1;
  i->A |= i->F & 0b0000001;
  i->F |= carry;
  
  i->F &= 0b11101101;
  return nop(i, inf);
}

enum Error rra(struct Instance* __restrict i, void** __restrict inf){
  uint8_t carry = (0b00000001 & i->A);
  i->A = i->A >> 1;
  i->A |= (i->F & 0b0000001) << 7;
  i->F |= carry;
  
  i->F &= 0b11101101;
  return nop(i, inf);
}
