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

enum Error bit_b_$hl$(struct Instance* __restrict i, void** __restrict inf){
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->H; //addr
    *(uint16_t*) inf[0] = *(uint16_t*) inf[0] << 8; //addr
    *(uint16_t*) inf[0] += i->L; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    uint8_t mask = 0b00000001 << ((i->instruction & 0b00111000) >> 3);
    i->F &= 0b10101101;
    i->F |= 0b00010000;
    if(!(i->A & mask)) {i->F |= 0b01000000;}
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error set_b_r(struct Instance* __restrict i, void** __restrict inf){
  uint8_t mask = 0b00000001 << ((i->instruction & 0b00111000) >> 3);
  switch (i->instruction & 0b00000111){
    default: return BAD_ARGUMENT;
    case A: i->A |= mask; break;
    case B: i->B |= mask; break;
    case C: i->C |= mask; break;
    case D: i->D |= mask; break;
    case E: i->E |= mask; break;
    case H: i->H |= mask; break;
    case L: i->L |= mask; break;
  }

  return nop(i, inf);
}

enum Error set_b_$hl$(struct Instance* __restrict i, void** __restrict inf){
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->H; //addr
    *(uint16_t*) inf[0] = *(uint16_t*) inf[0] << 8; //addr
    *(uint16_t*) inf[0] += i->L; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    uint8_t mask = 0b00000001 << ((i->instruction & 0b00111000) >> 3);
    i->tmp |= mask;
    i->MState = 3;
    i->TCycle = 1;
    return SUCCESS;
  }
  if (i->MState == 3) {
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error res_b_r(struct Instance* __restrict i, void** __restrict inf){
  uint8_t mask = !(0b00000001 << ((i->instruction & 0b00111000) >> 3));
  switch (i->instruction & 0b00000111){
    default: return BAD_ARGUMENT;
    case A: i->A &= mask; break;
    case B: i->B &= mask; break;
    case C: i->C &= mask; break;
    case D: i->D &= mask; break;
    case E: i->E &= mask; break;
    case H: i->H &= mask; break;
    case L: i->L &= mask; break;
  }

  return nop(i, inf);
}

enum Error res_b_$hl$(struct Instance* __restrict i, void** __restrict inf){
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->H; //addr
    *(uint16_t*) inf[0] = *(uint16_t*) inf[0] << 8; //addr
    *(uint16_t*) inf[0] += i->L; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    uint8_t mask = !(0b00000001 << ((i->instruction & 0b00111000) >> 3));
    i->tmp &= mask;
    i->MState = 3;
    i->TCycle = 1;
    return SUCCESS;
  }
  if (i->MState == 3) {
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}
