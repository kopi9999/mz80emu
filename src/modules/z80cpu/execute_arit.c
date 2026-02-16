#include "execute_arit.h"
#include "execute_control.h"

uint8_t getAddCarries(uint8_t a, uint8_t b, uint8_t previousCarry) {
  uint8_t out = 0;
  uint8_t tmp = 0;
  for (uint8_t i = 0; i < 8; i++) {
    tmp = (a & 0b00000001) + (b & 0b00000001);
    if (i) {tmp += (out >> (i - 1)) & 0b00000001;}
    else {tmp += previousCarry;}
    if (tmp > 1) {out += 1 << (i - 1);}
  }
  return out;
}

// ADD

enum Error add_a_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  uint8_t carries = 0;
  switch (i->instruction & 0b00000111) {
  case A: carries = getAddCarries(i->A, i->A, 0); i->A += i->A; break;
  case B: carries = getAddCarries(i->A, i->B, 0); i->A += i->B; break;
  case C: carries = getAddCarries(i->A, i->C, 0); i->A += i->C; break;
  case D: carries = getAddCarries(i->A, i->D, 0); i->A += i->D; break;
  case E: carries = getAddCarries(i->A, i->E, 0); i->A += i->E; break;
  case H: carries = getAddCarries(i->A, i->H, 0); i->A += i->H; break;
  case L: carries = getAddCarries(i->A, i->L, 0); i->A += i->L; break;
  default: return BAD_ARGUMENT;
  }

  uint8_t flags = 0;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  if (carries & 0b00001000) {flags += 0b00010000;} //H flag
  if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
  if (carries & 0b01000000) {flags += 0b00000001;} // C flag
  i->F = flags;
  return nop(i, inf);
  }  

enum Error add_a_n(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    i->PC += 1;
    uint8_t tmp = i->A;
    uint8_t carries = getAddCarries(i->A, i->tmp, 0);
    i->A += i->tmp;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if (carries & 0b00001000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if (carries & 0b01000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}  

enum Error add_a_$hl$(struct Instance *__restrict i, void **__restrict inf) {
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
    uint8_t tmp = i->A;
    uint8_t carries = getAddCarries(i->A, i->tmp, 0);
    i->A += i->tmp;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if (carries & 0b00001000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if (carries & 0b01000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

// ADC

enum Error adc_a_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  uint8_t carries = 0;
  if (i->F & 0b00000001) {i->tmp++;}
  switch (i->instruction & 0b00000111) {
  case A: carries = getAddCarries(i->A, i->A, 1); i->A += i->A; break;
  case B: carries = getAddCarries(i->A, i->B, 1); i->A += i->B; break;
  case C: carries = getAddCarries(i->A, i->C, 1); i->A += i->C; break;
  case D: carries = getAddCarries(i->A, i->D, 1); i->A += i->D; break;
  case E: carries = getAddCarries(i->A, i->E, 1); i->A += i->E; break;
  case H: carries = getAddCarries(i->A, i->H, 1); i->A += i->H; break;
  case L: carries = getAddCarries(i->A, i->L, 1); i->A += i->L; break;
  default: return BAD_ARGUMENT;
  }

  uint8_t flags = 0;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  if (carries & 0b00001000) {flags += 0b00010000;} //H flag
  if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
  if (carries & 0b01000000) {flags += 0b00000001;} // C flag
  i->F = flags;
  return nop(i, inf);
  }  

enum Error adc_a_n(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    i->PC += 1;
    uint8_t tmp = i->A;
    uint8_t carries = getAddCarries(i->A, i->tmp, 1);
    i->A += i->tmp;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if (carries & 0b00001000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if (carries & 0b01000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}  

enum Error adc_a_$hl$(struct Instance *__restrict i, void **__restrict inf) {
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
    uint8_t tmp = i->A;
    uint8_t carries = getAddCarries(i->A, i->tmp, 1);
    i->A += i->tmp;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if (carries & 0b00001000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if (carries & 0b01000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}
