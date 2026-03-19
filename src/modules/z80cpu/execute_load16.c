#include "execute_load16.h"
#include "execute_control.h"

enum Error ld_dd_nn(struct Instance *__restrict i, void **__restrict inf) {
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
      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->B = i->tmp; break;
        case DE: i->D = i->tmp; break;
        case HL: i->H = i->tmp; break;
        case SP: i->SP = i->tmp; i->SP = i->SP << 8; break;
      }
      i->TCycle = 1;
      i->PC++;
      *(uint16_t*) inf[0] = i->PC; //addr
      i->stateIterator = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->C = i->tmp; break;
        case DE: i->E = i->tmp; break;
        case HL: i->L = i->tmp; break;
        case SP: i->SP |= i->tmp; break;
      }
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error ld_hl_$nn$(struct Instance *__restrict i, void **__restrict inf) {
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
      *(uint16_t*) inf[0] = i->tmpAddr; //addr
      i->stateIterator = 2;
      return SUCCESS;
    }
    if (i->stateIterator == 2) {
      i->L = i->tmp;
      i->TCycle = 1;
      *(uint16_t*) inf[0] += 1; //addr
      i->stateIterator = 3;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      i->H = i->tmp;
      return nop(i, inf);
    }
  }

  return BAD_ARGUMENT;
}

enum Error ld_dd_$nn$(struct Instance *__restrict i, void **__restrict inf) {
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
      *(uint16_t*) inf[0] = i->tmpAddr; //addr
      i->stateIterator = 2;
      return SUCCESS;
    }
    if (i->stateIterator == 2) {
      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->C = i->tmp; break;
        case DE: i->E = i->tmp; break;
        case HL: i->L = i->tmp; break;
        case SP: i->SP = i->tmp; break;
      }
      i->TCycle = 1;
      *(uint16_t*) inf[0] += 1; //addr
      i->stateIterator = 3;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->B = i->tmp; break;
        case DE: i->D = i->tmp; break;
        case HL: i->H = i->tmp; break;
      case SP: i->SP = i->tmp << 8; break;
      }
      return nop(i, inf);
    }
  }

  return BAD_ARGUMENT;
}
