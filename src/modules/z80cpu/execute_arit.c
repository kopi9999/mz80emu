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
  if (carries & 0b10000000) {flags += 0b00000001;} // C flag
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
    if (carries & 0b10000000) {flags += 0b00000001;} // C flag
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
    if (carries & 0b10000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

// ADC

enum Error adc_a_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  uint8_t carries = 0;
  uint8_t carry = i->F & 0b00000001;
  switch (i->instruction & 0b00000111) {
  case A: carries = getAddCarries(i->A, i->A, carry); i->A += i->A + carry; break;
  case B: carries = getAddCarries(i->A, i->B, carry); i->A += i->B + carry; break;
  case C: carries = getAddCarries(i->A, i->C, carry); i->A += i->C + carry; break;
  case D: carries = getAddCarries(i->A, i->D, carry); i->A += i->D + carry; break;
  case E: carries = getAddCarries(i->A, i->E, carry); i->A += i->E + carry; break;
  case H: carries = getAddCarries(i->A, i->H, carry); i->A += i->H + carry; break;
  case L: carries = getAddCarries(i->A, i->L, carry); i->A += i->L + carry; break;
  default: return BAD_ARGUMENT;
  }

  uint8_t flags = 0;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  if (carries & 0b00001000) {flags += 0b00010000;} //H flag
  if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
  if (carries & 0b10000000) {flags += 0b00000001;} // C flag
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
    uint8_t carry = i->F & 0b00000001;
    uint8_t carries = getAddCarries(i->A, i->tmp, carry);
    i->A += i->tmp + carry;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if (carries & 0b00001000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if (carries & 0b10000000) {flags += 0b00000001;} // C flag
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
    uint8_t carry = i->F & 0b00000001;
    uint8_t carries = getAddCarries(i->A, i->tmp, carry);
    i->A += i->tmp + carry;

    uint8_t flags = 0;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    if (carries & 0b00001000) {flags += 0b00010000;} //H flag
    if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
    if (carries & 0b10000000) {flags += 0b00000001;} // C flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error sub_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  uint8_t carries = 0;
  switch (i->instruction & 0b00000111) {
  case A: carries = getAddCarries(i->A, (!i->A + 1), 0); i->A -= i->A; break;
  case B: carries = getAddCarries(i->A, (!i->B + 1), 0); i->A -= i->B; break;
  case C: carries = getAddCarries(i->A, (!i->C + 1), 0); i->A -= i->C; break;
  case D: carries = getAddCarries(i->A, (!i->D + 1), 0); i->A -= i->D; break;
  case E: carries = getAddCarries(i->A, (!i->E + 1), 0); i->A -= i->E; break;
  case H: carries = getAddCarries(i->A, (!i->H + 1), 0); i->A -= i->H; break;
  case L: carries = getAddCarries(i->A, (!i->L + 1), 0); i->A -= i->L; break;
  default: return BAD_ARGUMENT;
  }

  carries = !carries;
  uint8_t flags = 0b00000010;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  if (carries & 0b00001000) {flags += 0b00010000;} //H flag
  if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
  if (carries & 0b10000000) {flags += 0b00000001;} // C flag
  i->F = flags;
  return nop(i, inf);
  }  

enum Error sub_n(struct Instance *__restrict i, void **__restrict inf) {
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
    uint8_t carries = getAddCarries(i->A, (!i->tmp + 1), 0);
    carries = !carries;
    i->A -= i->tmp;

    uint8_t flags = 0b00000010;
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

enum Error sub_$hl$(struct Instance *__restrict i, void **__restrict inf) {
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
    uint8_t carries = getAddCarries(i->A, (!i->tmp + 1), 0);
    carries = !carries;
    i->A -= i->tmp;

    uint8_t flags = 0b00000010;
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

enum Error sbc_a_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  uint8_t carries = 0;
  uint8_t carry = i->F & 0b00000001;
  switch (i->instruction & 0b00000111) {
  case A: carries = getAddCarries(i->A, (!i->A + 1), carry); i->A -= i->A - carry; break;
  case B: carries = getAddCarries(i->A, (!i->B + 1), carry); i->A -= i->B - carry; break;
  case C: carries = getAddCarries(i->A, (!i->C + 1), carry); i->A -= i->C - carry; break;
  case D: carries = getAddCarries(i->A, (!i->D + 1), carry); i->A -= i->D - carry; break;
  case E: carries = getAddCarries(i->A, (!i->E + 1), carry); i->A -= i->E - carry; break;
  case H: carries = getAddCarries(i->A, (!i->H + 1), carry); i->A -= i->H - carry; break;
  case L: carries = getAddCarries(i->A, (!i->L + 1), carry); i->A -= i->L - carry; break;
  default: return BAD_ARGUMENT;
  }

  carries = !carries;
  uint8_t flags = 0b00000010;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  if (carries & 0b00001000) {flags += 0b00010000;} //H flag
  if (i->tmp > i->A) {flags += 0b00000100;} //P/V flag
  if (carries & 0b10000000) {flags += 0b00000001;} // C flag
  i->F = flags;
  return nop(i, inf);
  }  

enum Error sbc_a_n(struct Instance *__restrict i, void **__restrict inf) {
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
    uint8_t carry = i->F & 0b00000001;
    uint8_t carries = getAddCarries(i->A, (!i->tmp + 1), carry);
    carries = !carries;
    i->A -= i->tmp;

    uint8_t flags = 0b00000010;
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

enum Error sbc_a_$hl$(struct Instance *__restrict i, void **__restrict inf) {
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
    uint8_t carry = i->F & 0b00000001;
    uint8_t carries = getAddCarries(i->A, (!i->tmp + 1), carry);
    carries = !carries;
    i->A -= i->tmp;

    uint8_t flags = 0b00000010;
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

enum Error and_r(struct Instance *__restrict i, void **__restrict inf) {
  i->tmp = i->A;
  switch (i->instruction & 0b00000111) {
  case A: i->A &= i->A; break;
  case B: i->A &= i->B; break;
  case C: i->A &= i->C; break;
  case D: i->A &= i->D; break;
  case E: i->A &= i->E; break;
  case H: i->A &= i->H; break;
  case L: i->A &= i->L; break;
  default: return BAD_ARGUMENT;
  }

  uint8_t flags = 0b00010000;
  if (i->A == 0) {flags += 0b01000000;} //Z flag
  if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
  i->F = flags;
  return nop(i, inf);
  }  

enum Error and_n(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    i->PC += 1;
    i->A &= i->tmp;

    uint8_t flags = 0b00010000;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}  

enum Error and_$hl$(struct Instance *__restrict i, void **__restrict inf) {
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
    i->A &= i->tmp;

    uint8_t flags = 0b00000010;
    if (i->A == 0) {flags += 0b01000000;} //Z flag
    if (i->A & 0b10000000) {flags += 0b10000000;} //S flag
    i->F = flags;
    
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}
