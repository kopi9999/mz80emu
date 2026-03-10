#include "execute_load.h"
#include "execute_control.h"

enum Error jp_nn(struct Instance*__restrict i, void**__restrict inf) {
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
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error jp_cc_nn(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    switch ((i->instruction & 0b00111000) >> 3) {
    case 0: //nonzero
      if (i->F & 0b00000010) {i->PC += 2; return nop(i, inf);}
      break;
    case 1: //zero
      if (i->F & 0b00000010) {break;}
      i->PC += 2;
      return nop(i, inf);
    case 2: //nocarry
      if (i->F & 0b00000001) {i->PC += 2; return nop(i, inf);}
      break;
    case 3: //carry
      if (i->F & 0b00000001) {break;}
      i->PC += 2;
      return nop(i, inf);
    case 4: //pairity odd      
      if (i->F & 0b00000100) {i->PC += 2; return nop(i, inf);}
      break;
    case 5: //pairity even
      if (i->F & 0b00000100) {break;}
      i->PC += 2;
      return nop(i, inf);
    case 6: //sign positive
      if (i->F & 0b10000000) {break;}
      i->PC += 2;
      return nop(i, inf);
    case 7: //sign negative
      if (i->F & 0b10000000) {i->PC += 2; return nop(i, inf);}
      break;
    }
    
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
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error jr_e(struct Instance*__restrict i, void**__restrict inf) {
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
      i->TCycle = 1;
      i->PC++;
      i->stateIterator = 1;
      i->skipTick = 1;
      return SUCCESS;
    }
    if (i->stateIterator < 5) {
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 5) {
      i->tmp = i->tmpAddr;
      int8_t tmp = (int8_t) i->tmp;
      i->PC += tmp;
      i->skipTick = 0;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error jr_c_e(struct Instance*__restrict i, void**__restrict inf) {
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
      i->TCycle = 1;
      i->PC++;
      
      if (i->F & 0b00000001) {
        return nop(i, inf);
      }
      i->stateIterator = 1;
      i->skipTick = 1;
      return SUCCESS;
    }
    if (i->stateIterator < 5) {
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 5) {
      i->tmp = i->tmpAddr;
      int8_t tmp = (int8_t) i->tmp;
      i->PC += tmp;
      i->skipTick = 0;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}
