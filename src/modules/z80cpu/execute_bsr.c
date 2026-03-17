#include "execute_bsr.h"
#include "execute_control.h"

enum Error bit_b_r(struct Instance* __restrict i, void** __restrict inf){
  uint8_t mask = 0b00000001 << ((i->instruction & 0b00111000) >> 3);
  i->F &= 0b10101101;
  i->F |= 0b00010000;
  switch (i->instruction & 0b00000111){
    default: return BAD_ARGUMENT;
    case A: if(!(i->A & mask)) {i->F |= 0b01000000;} break;
    case B: if(!(i->B & mask)) {i->F |= 0b01000000;} break;
    case C: if(!(i->C & mask)) {i->F |= 0b01000000;} break;
    case D: if(!(i->D & mask)) {i->F |= 0b01000000;} break;
    case E: if(!(i->E & mask)) {i->F |= 0b01000000;} break;
    case H: if(!(i->H & mask)) {i->F |= 0b01000000;} break;
    case L: if(!(i->L & mask)) {i->F |= 0b01000000;} break;
  }

  return nop(i, inf);
}
