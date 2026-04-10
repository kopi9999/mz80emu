#include "execute_call.h"
#include "execute_control.h"

enum Error call_nn(struct Instance* __restrict i, void** __restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->PC++;
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->tmpAddr = i->tmp;
      i->TCycle = 1;
      *(uint16_t*) inf[0] = i->PC; //addr
      i->PC++;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->tmpAddr |= i->tmp << 8;
      i->MState = 3;
      i->TCycle = 1;
      i->SP--;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->tmp = i->PC >> 8;
      i->stateIterator++;
      return SUCCESS;
    }
  }
  if (i->MState == 3){
    if (i->stateIterator == 2) {
      i->SP--;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->tmp = i->PC & 0x00FF;
      i->TCycle = 1;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error call_cc_nn(struct Instance* __restrict i, void** __restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->PC++;
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->tmpAddr = i->tmp;
      i->TCycle = 1;
      *(uint16_t*) inf[0] = i->PC; //addr
      i->PC++;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->tmpAddr |= i->tmp << 8;
      switch ((i->instruction & 0b00111000) >> 3) {
        case 0: if (i->F & 0b01000000) {return nop(i, inf);} break; // non zero
        case 1: if (i->F & 0b01000000) {break;} return nop(i, inf); // zero
        case 2: if (i->F & 0b00000001) {return nop(i, inf);} break; // non carry
        case 3: if (i->F & 0b00000001) {break;} return nop(i, inf); // carry
        case 4: if (i->F & 0b00000000) {return nop(i, inf);} break; // pairity odd
        case 5: if (i->F & 0b00000100) {break;} return nop(i, inf); // pairity even
        case 6: if (i->F & 0b10000100) {return nop(i, inf);} break; // sign positive
        case 7: if (i->F & 0b10000000) {break;} return nop(i, inf); // sign negative
      }
      i->MState = 3;
      i->TCycle = 1;
      i->SP--;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->tmp = i->PC >> 8;
      i->stateIterator++;
      return SUCCESS;
    }
  }
  if (i->MState == 3){
    if (i->stateIterator == 2) {
      i->SP--;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->tmp = i->PC & 0x00FF;
      i->TCycle = 1;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error ret(struct Instance* __restrict i, void** __restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->SP; //addr
    i->SP++;
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->tmpAddr = i->tmp;
      i->TCycle = 1;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->SP++;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->tmpAddr |= i->tmp << 8;
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}  
 
enum Error ret_cc(struct Instance* __restrict i, void** __restrict inf) {
  if (i->MState == 1) {
    switch ((i->instruction & 0b00111000) >> 3) {
      case 0: if (i->F & 0b01000000) {return nop(i, inf);} break; // non zero
      case 1: if (i->F & 0b01000000) {break;} return nop(i, inf); // zero
      case 2: if (i->F & 0b00000001) {return nop(i, inf);} break; // non carry
      case 3: if (i->F & 0b00000001) {break;} return nop(i, inf); // carry
      case 4: if (i->F & 0b00000000) {return nop(i, inf);} break; // pairity odd
      case 5: if (i->F & 0b00000100) {break;} return nop(i, inf); // pairity even
      case 6: if (i->F & 0b10000100) {return nop(i, inf);} break; // sign positive
      case 7: if (i->F & 0b10000000) {break;} return nop(i, inf); // sign negative
      default: return BAD_ARGUMENT;
    }
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->SP; //addr
    i->SP++;
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->tmpAddr = i->tmp;
      i->TCycle = 1;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->SP++;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->tmpAddr |= i->tmp << 8;
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error rst_p(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1){
    switch ((i->instruction & 0b00111000) >> 3) {
      case 0: i->tmpAddr = 0x0000; break;
      case 1: i->tmpAddr = 0x0008; break;
      case 2: i->tmpAddr = 0x0010; break;
      case 3: i->tmpAddr = 0x0018; break;
      case 4: i->tmpAddr = 0x0020; break;
      case 5: i->tmpAddr = 0x0028; break;
      case 6: i->tmpAddr = 0x0030; break;
      case 7: i->tmpAddr = 0x0038; break;
    }
    i->MState = 3;
    i->TCycle = 1;

    i->SP--;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->SP; //addr
    i->tmp = i->PC >> 8;

    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 3) {
    if (i->stateIterator == 0) {
      i->TCycle = 1;
      i->SP--;
      *(uint16_t*) inf[0] = i->SP; //addr
      i->tmp = i->PC & 0x00FF;
      
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->PC = i->tmpAddr;
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}
