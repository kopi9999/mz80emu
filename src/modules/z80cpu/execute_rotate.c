#include "execute_rotate.h"
#include "execute_control.h"

enum Error rlca(struct Instance* __restrict i, void** __restrict inf){
  i->F |= (0b10000000 & i->A) >> 7;
  i->A = i->A << 1;
  i->A |= i->F & 0b00000001;

  i->F &= 0b11101101;
  return nop(i, inf);
}

enum Error rla(struct Instance* __restrict i, void** __restrict inf){
  uint8_t carry = (0b10000000 & i->A) >> 7;
  i->A = i->A << 1;
  i->A |= i->F & 0b00000001;
  i->F |= carry;
  
  i->F &= 0b11101101;
  return nop(i, inf);
}

enum Error rra(struct Instance* __restrict i, void** __restrict inf){
  uint8_t carry = (0b00000001 & i->A);
  i->A = i->A >> 1;
  i->A |= (i->F & 0b00000001) << 7;
  i->F |= carry;
  
  i->F &= 0b11101101;
  return nop(i, inf);
}

enum Error rlc_r(struct Instance* __restrict i, void** __restrict inf){
  i->F = 0;
  switch (i->instruction & 0b00000111) {
    case A:
      i->F |= (0b10000000 & i->A) >> 7;
      i->A = i->A << 1;
      i->A |= i->F & 0b00000001;
      if (i->A == 0) {i->F |= 0b01000000;} //Z flag
      if (i->A & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->A) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    case B:
      i->F |= (0b10000000 & i->B) >> 7;
      i->B = i->B << 1;
      i->B |= i->F & 0b00000001;
      if (i->B == 0) {i->F |= 0b01000000;} //Z flag
      if (i->B & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->B) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    case C:
      i->F |= (0b10000000 & i->C) >> 7;
      i->C = i->C << 1;
      i->C |= i->F & 0b00000001;
      if (i->C == 0) {i->F |= 0b01000000;} //Z flag
      if (i->C & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->C) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    case D:
      i->F |= (0b10000000 & i->D) >> 7;
      i->D = i->D << 1;
      i->D |= i->F & 0b00000001;
      if (i->D == 0) {i->F |= 0b01000000;} //Z flag
      if (i->D & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->D) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    case E:
      i->F |= (0b10000000 & i->E) >> 7;
      i->E = i->E << 1;
      i->E |= i->F & 0b00000001;
      if (i->E == 0) {i->F |= 0b01000000;} //Z flag
      if (i->E & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->E) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    case H:
      i->F |= (0b10000000 & i->H) >> 7;
      i->H = i->H << 1;
      i->H |= i->F & 0b00000001;
      if (i->H == 0) {i->F |= 0b01000000;} //Z flag
      if (i->H & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->H) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    case L:
      i->F |= (0b10000000 & i->L) >> 7;
      i->L = i->L << 1;
      i->L |= i->F & 0b00000001;
      if (i->L == 0) {i->F |= 0b01000000;} //Z flag
      if (i->L & 0b10000000) {i->F |= 0b10000000;} //S flag
      if (pairity(i->L) % 2 == 0) {i->F |= 0b00000100;} //P/V flag
      break;
    default: return BAD_ARGUMENT;
  }

  return nop(i, inf);
}
