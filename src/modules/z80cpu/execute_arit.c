#include "execute_arit.h"
#include "execute_control.h"

enum Error add_a_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  switch (i->instruction & 0b00000111) {
  case A: i->A += i->A; break;
  case B: i->A += i->B; break;
  case C: i->A += i->C; break;
  case D: i->A += i->D; break;
  case E: i->A += i->E; break;
  case H: i->A += i->H; break;
  case L: i->A += i->L; break;
  default: return BAD_ARGUMENT;
  }

  uint8_t flags = 0;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  if ((i->A ^ i->tmp) & 0b00010000) {flags += 0b00010000;} //H flag
  if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
  if ((i->A ^ i->tmp) & 0b10000000) {flags += 0b00000001;} // C flag
  i->F = flags;
  return nop(i, inf);
  }  

enum Error add_a_n(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->registerIn = i->PC;
    return SUCCESS;
  }
  if (i->MState == 2) {
    i->PC += 1;
    uint8_t tmp = i->A;
    i->A += i->tmp;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if ((i->A ^ tmp) & 0b00010000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if ((i->A ^ tmp) & 0b10000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}  
