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

enum Error rlc_r(struct Instance* __restrict i, void** __restrict inf){
  switch (i->instruction & 0b00000111) {
    case A:
      i->F |= (0b10000000 & i->A) >> 7;
      i->A = i->A << 1;
      i->A |= i->F & 0b0000001;
      break;
    case B:
      i->F |= (0b10000000 & i->B) >> 7;
      i->B = i->B << 1;
      i->B |= i->F & 0b0000001;
      break;
    case C:
      i->F |= (0b10000000 & i->C) >> 7;
      i->C = i->C << 1;
      i->C |= i->F & 0b0000001;
      break;
    case D:
      i->F |= (0b10000000 & i->D) >> 7;
      i->D = i->D << 1;
      i->D |= i->F & 0b0000001;
      break;
    case E:
      i->F |= (0b10000000 & i->E) >> 7;
      i->E = i->E << 1;
      i->E |= i->F & 0b0000001;
      break;
    case H:
      i->F |= (0b10000000 & i->H) >> 7;
      i->H = i->H << 1;
      i->H |= i->F & 0b0000001;
      break;
    case L:
      i->F |= (0b10000000 & i->L) >> 7;
      i->L = i->L << 1;
      i->L |= i->F & 0b0000001;
      break;
    default: return BAD_ARGUMENT;
  }

  i->F &= 0b11101101;
  return nop(i, inf);
}
