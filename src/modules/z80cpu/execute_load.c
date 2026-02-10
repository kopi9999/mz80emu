#include "execute_load.h"
#include "execute_control.h"

uint8_t getRegisterValue(struct Instance* __restrict i, enum Register r) {
  switch (r) {
  case A: return(i->A);
  case B: return(i->B);
  case C: return(i->C);
  case D: return(i->D);
  case E: return(i->E);
  case H: return(i->H);
  case L: return(i->L);
  default: return(0);
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

  return nop(i, inf);
}

enum Error ld_r_$hl$(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->H; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8; //addr
    *(uint16_t *)inf[0] += i->L; //addr
    i->registerIn = (i->instruction & 0b00111000) >> 3;
    return SUCCESS;
  }
  if (i->MState == 2) {
    switch (i->registerIn) {
    case A: i->A = i->tmp; break;
    case B: i->B = i->tmp; break;
    case C: i->C = i->tmp; break;
    case D: i->D = i->tmp; break;
    case E: i->E = i->tmp; break;
    case H: i->H = i->tmp; break;
    case L: i->L = i->tmp; break;
    default: return BAD_ARGUMENT;
    }
    i->PC++;
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_r_n(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->registerIn = (i->instruction & 0b00111000) >> 3;
    return SUCCESS;
  }

  if (i->MState == 2) {
    switch (i->registerIn) {
    case A: i->A = i->tmp; break;
    case B: i->B = i->tmp; break;
    case C: i->C = i->tmp; break;
    case D: i->D = i->tmp; break;
    case E: i->E = i->tmp; break;
    case H: i->H = i->tmp; break;
    case L: i->L = i->tmp; break;
    default: return BAD_ARGUMENT;
    }
    i->PC++;
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_$hl$_r(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 3;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->H; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8; //addr
    *(uint16_t *)inf[0] += i->L; //addr

    i->registerOut = i->instruction & 0b00000111;
    switch (i->registerOut) {
    case A: i->tmp = i->A; break;
    case B: i->tmp = i->B; break;
    case C: i->tmp = i->C; break;
    case D: i->tmp = i->D; break;
    case E: i->tmp = i->E; break;
    case H: i->tmp = i->H; break;
    case L: i->tmp = i->L; break;
    default: return BAD_ARGUMENT;
    }
    
    return SUCCESS;
  }

  if (i->MState == 3) {
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_a_$bc$(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->B; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8; //addr
    *(uint16_t *)inf[0] += i->C; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    i->A = i->tmp;
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_a_$de$(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->D; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8; //addr
    *(uint16_t *)inf[0] += i->E; //addr
    return SUCCESS;
  }
  if (i->MState == 2) {
    i->A = i->tmp;
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_a_$nn$(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->tmpAddr = i->tmp;
      i->tmpAddr = i->tmpAddr << 8;
      i->TCycle = 1;
      i->PC++;
      *(uint16_t*) inf[0] = i->PC; //addr
      i->stateIterator = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->tmpAddr += i->tmp;
      i->TCycle = 1;
      i->PC++;
      *(uint16_t*) inf[0] = i->tmpAddr; //addr
      i->stateIterator = 2;
      return SUCCESS;
    }
    if (i->stateIterator == 2) {
      i->A = i->tmp;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error ld_$bc$_a(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 3;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->B; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8; //addr
    *(uint16_t *)inf[0] += i->C; //addr
    i->A = i->tmp;
    return SUCCESS;
  }
  if (i->MState == 3) {
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_$de$_a(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 3;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->D; //addr
    *(uint16_t*) inf[0] = (*(uint16_t*) inf[0]) << 8; //addr
    *(uint16_t *)inf[0] += i->E; //addr
    i->A = i->tmp;
    return SUCCESS;
  }
  if (i->MState == 3) {
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ld_$nn$_a(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->tmpAddr = i->tmp;
      i->tmpAddr = i->tmpAddr << 8;
      i->TCycle = 1;
      i->PC++;
      *(uint16_t*) inf[0] = i->PC; //addr
      i->stateIterator = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->tmpAddr += i->tmp;
      i->TCycle = 1;
      i->MState = 3;
      i->PC++;
      *(uint16_t*) inf[0] = i->tmpAddr; //addr
      i->tmp = i->A;
      i->stateIterator = 2;
      return SUCCESS;
    }
  }

  if (i->MState == 3) {
    return nop(i, inf);
  }

  return BAD_ARGUMENT;
}
