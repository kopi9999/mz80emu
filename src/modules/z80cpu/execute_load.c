#include "execute_load.h"

uint8_t getRegisterValue(struct Instance* __restrict i, enum Register r) {
  switch (r) {
  case A: return(i->A);
  case B: return(i->B);
  case C: return(i->C);
  case D: return(i->D);
  case E: return(i->E);
  case H: return(i->H);
  case L: return(i->L);
  case UNDEFINED: return(0);
  }

}

enum Error ld_r_rp(struct Instance* __restrict i, void** __restrict inf) {

  switch (i->registerIn) {
  case A: i->A = getRegisterValue(i, A); break;
  case B: i->B = getRegisterValue(i, B); break;
  case C: i->C = getRegisterValue(i, C); break;
  case D: i->D = getRegisterValue(i, D); break;
  case E: i->E = getRegisterValue(i, E); break;
  case H: i->H = getRegisterValue(i, H); break;
  case L: i->L = getRegisterValue(i, L); break;
  case UNDEFINED: return(BAD_ARGUMENT);
  }

  i->MState = 1;
  i->TCycle = 1;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}

enum Error ld_r_$hl$(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = H; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8;
    *(uint16_t *)inf[0] += L;
    i->registerIn = (i->instruction & 0x00111000) >> 3;
    return SUCCESS;
  }
  if (i->MState == 2) {
    switch (i->registerIn) {
    case A: i->A = i->tmp;
    case B: i->B = i->tmp;
    case C: i->C = i->tmp;
    case D: i->D = i->tmp;
    case E: i->E = i->tmp;
    case H: i->H = i->tmp;
    case L: i->L = i->tmp;
    case UNDEFINED: return BAD_ARGUMENT;
    }

    i->MState = 1;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 1; // m1
    *(uint16_t*) inf[0] = i->PC;
    return SUCCESS;
  }
  return BAD_ARGUMENT;
}
