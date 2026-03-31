#include "execute_load16.h"
#include "execute_control.h"

enum Error ld_dd_nn(struct Instance *__restrict i, void **__restrict inf) {
  if (i->currentOverride && i->instruction != 0x21){ return BAD_ARGUMENT;}
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
      if (i->currentOverride == IX_OVERRIDE) {
	i->IX = i->tmp;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->IY = i->tmp;
      }
      else {
	switch ((i->instruction & 0b00110000) >> 4) {
          default: return BAD_ARGUMENT;
          case BC: i->C = i->tmp; break;
          case DE: i->E = i->tmp; break;
          case HL: i->L = i->tmp; break;
          case SP: i->SP = i->tmp; break;
        }
      }
      i->TCycle = 1;
      i->PC++;
      *(uint16_t*) inf[0] = i->PC; //addr
      i->stateIterator = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      if (i->currentOverride == IX_OVERRIDE) {
	i->IX = i->tmp << 8;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->IY = i->tmp << 8;
      }
      else {
	switch ((i->instruction & 0b00110000) >> 4) {
          default: return BAD_ARGUMENT;
          case BC: i->B = i->tmp; break;
          case DE: i->D = i->tmp; break;
          case HL: i->H = i->tmp; break;
          case SP: i->SP |= i->tmp << 8; break;
        }
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
      if (i->currentOverride == IX_OVERRIDE) {
	i->IX = i->tmp;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->IY = i->tmp;
      }
      else {
	i->L = i->tmp;
      }      
      i->TCycle = 1;
      *(uint16_t*) inf[0] += 1; //addr
      i->PC++;
      i->stateIterator = 3;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      if (i->currentOverride == IX_OVERRIDE) {
	i->IX |= i->tmp << 8;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->IY |= i->tmp << 8;
      }
      else {
	i->H = i->tmp;
      }
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

enum Error ld_$nn$_hl(struct Instance *__restrict i, void **__restrict inf) {
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
      *(uint16_t*) inf[0] = i->tmpAddr; //addr
      if (i->currentOverride == IX_OVERRIDE) {
	i->tmp = i->IX & 0x00FF;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->tmp = i->IY & 0x00FF;
      }
      else {
	i->tmp = i->L;
      }
      i->stateIterator = 2;
      return SUCCESS;
    }
  }
  if (i->MState == 3) {
    if (i->stateIterator == 2) {
      i->TCycle = 1;
      *(uint16_t*) inf[0] += 1; //addr
      if (i->currentOverride == IX_OVERRIDE) {
	i->tmp = i->IX >> 8;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->tmp = i->IY >> 8;
      }
      else {
	i->tmp = i->H;
      }
      i->stateIterator = 3;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      return nop(i, inf);
    }
  }

  return BAD_ARGUMENT;
}

enum Error ld_$nn$_dd(struct Instance *__restrict i, void **__restrict inf) {
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
      *(uint16_t*) inf[0] = i->tmpAddr; //addr

      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->tmp = i->C; break;
        case DE: i->tmp = i->E; break;
        case HL: i->tmp = i->L; break;
        case SP: i->tmp = i->SP & 0b0000000011111111; break;
      }
      i->stateIterator = 2;
      return SUCCESS;
    }
  }
  if (i->MState == 3) {
    if (i->stateIterator == 2) {
      i->TCycle = 1;
      *(uint16_t*) inf[0] += 1; //addr
      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->tmp = i->B; break;
        case DE: i->tmp = i->D; break;
        case HL: i->tmp = i->H; break;
        case SP: i->tmp = (i->SP & 0b1111111100000000) >> 8; break;
      }
      i->stateIterator = 3;
      return SUCCESS;
    }
    if (i->stateIterator == 3) {
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error ld_sp_hl(struct Instance *__restrict i, void **__restrict inf) {
  if (i->stateIterator == 0) {
    i->stateIterator = 1;
    if (i->currentOverride == IX_OVERRIDE) {
      i->SP = i->IX;
    }
    else if (i->currentOverride == IY_OVERRIDE) {
      i->SP = i->IY;
    }
    else {
      i->SP = i->H;
      i->SP = i->SP << 8;
    }
    i->skipTick = 1;
    return SUCCESS;
  }
  if (i->stateIterator == 1) {
    if (!i->currentOverride){
      i->SP |= i->L;
    }      
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error push_qq(struct Instance *__restrict i, void **__restrict inf) {
  if (i->currentOverride && i->instruction != 0xE5){ return BAD_ARGUMENT;}
  if (i->MState == 1) {
    i->MState = 3;
    i->TCycle = 1;
    i->SP--;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->SP; //addr
    if (i->currentOverride == IX_OVERRIDE) {
      i->tmp = i->IX >> 8;
    }
    else if (i->currentOverride == IY_OVERRIDE) {
      i->tmp = i->IY >> 8;
    }
    else {
      switch ((i->instruction & 0b00110000) >> 4) {
        default: return BAD_ARGUMENT;
        case BC: i->tmp = i->B; break;
        case DE: i->tmp = i->D; break;
        case HL: i->tmp = i->H; break;
        case SP: i->tmp = i->A; break; //AF
      }
    }
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 3) {
    if (i->stateIterator == 0) {
      i->TCycle = 1;
      i->SP--;
      *(uint16_t*) inf[0] -= 1; //addr
      if (i->currentOverride == IX_OVERRIDE) {
	i->tmp = i->IX & 0x00FF;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->tmp = i->IY & 0x00FF;
      }
      else {
	switch ((i->instruction & 0b00110000) >> 4) {
          default: return BAD_ARGUMENT;
          case BC: i->tmp = i->C; break;
          case DE: i->tmp = i->E; break;
          case HL: i->tmp = i->L; break;
          case SP: i->tmp = i->F; break; //AF
        }
      }
      i->stateIterator = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}

enum Error pop_qq(struct Instance *__restrict i, void **__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->SP; //addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  if (i->MState == 2) {
    if (i->stateIterator == 0) {
      i->TCycle = 1;
      i->SP++;
      *(uint16_t*) inf[0] += 1; //addr
      if (i->currentOverride == IX_OVERRIDE) {
	i->tmp = i->IX & 0x00FF;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->tmp = i->IY & 0x00FF;
      }
      else {
	switch ((i->instruction & 0b00110000) >> 4) {
          default: return BAD_ARGUMENT;
          case BC: i->tmp = i->C; break;
          case DE: i->tmp = i->E; break;
          case HL: i->tmp = i->L; break;
          case SP: i->tmp = i->F; break; //AF
        }
      }
      i->stateIterator = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->SP++;
      if (i->currentOverride == IX_OVERRIDE) {
	i->tmp = i->IX >> 8;
      }
      else if (i->currentOverride == IY_OVERRIDE) {
	i->tmp = i->IY >> 8;
      }
      else {
	switch ((i->instruction & 0b00110000) >> 4) {
          default: return BAD_ARGUMENT;
          case BC: i->tmp = i->B; break;
          case DE: i->tmp = i->D; break;
          case HL: i->tmp = i->H; break;
          case SP: i->tmp = i->A; break; //AF
        }
      }
      return nop(i, inf);
    }
  }
  return BAD_ARGUMENT;
}
