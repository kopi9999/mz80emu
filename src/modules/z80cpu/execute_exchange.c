#include "execute_exchange.h"
#include "execute_control.h"

enum Error ex_de_hl(struct Instance*__restrict i, void**__restrict inf) {
  i->tmp = i->H;
  i->H = i->D;
  i->D = i->tmp;

  i->tmp = i->L;
  i->L = i->E;
  i->E = i->tmp;
  return nop(i, inf);
}

enum Error ex_af_af(struct Instance*__restrict i, void**__restrict inf) {
  i->tmp = i->A;
  i->A = i->Aprim;
  i->Aprim = i->tmp;
  
  i->tmp = i->F;
  i->F = i->Fprim;
  i->Fprim = i->tmp;
  return nop(i, inf);
}

enum Error exx(struct Instance*__restrict i, void**__restrict inf) {
  i->tmp = i->B;
  i->B = i->Bprim;
  i->Bprim = i->tmp;

  i->tmp = i->C;
  i->C = i->Cprim;
  i->Cprim = i->tmp;

  i->tmp = i->D;
  i->D = i->Dprim;
  i->Dprim = i->tmp;

  i->tmp = i->E;
  i->E = i->Eprim;
  i->Eprim = i->tmp;

  i->tmp = i->H;
  i->H = i->Hprim;
  i->Hprim = i->tmp;

  i->tmp = i->L;
  i->L = i->Lprim;
  i->Lprim = i->tmp;
  return nop(i, inf);
}

enum Error ex_$sp$_hl(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->SP; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    if (i->stateIterator == 0) {      
      uint8_t tmp = i->L;
      i->L = i->tmp;
      i->tmp = tmp;
      i->MState = 3;
      i->TCycle = 1;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      uint8_t tmp = i->H;
      i->H = i->tmp;
      i->tmp = tmp;
      i->MState = 3;
      i->TCycle = 1;
      return SUCCESS;
    }
    if (i->stateIterator < 8) {
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 8) {
      i->skipTick = 0;
      return nop(i, inf);
    }
  }

  if (i->MState == 3) {
    if (i->stateIterator == 0) {
      *(uint16_t*) inf[0] += 1;
      i->MState = 2;
      i->TCycle = 1;
      i->stateIterator++;
      return SUCCESS;
    }
    if (i->stateIterator == 1) {
      i->skipTick = 1;
      i->stateIterator++;
      return SUCCESS;
    }
  }
  return BAD_ARGUMENT;
}

enum Error ldi(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->H; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    *(uint16_t *)inf[0] = i->E << 8; // addr
    *(uint16_t *)inf[0] |= i->D; // addr
    i->MState = 3;
    i->TCycle = 1;
    return SUCCESS;
  }  
  if (i->MState == 3) {
    increment16(&(i->D), &(i->E));
    increment16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    i->F &= 0b11101001;
    if (i->B != 0 && i->C != 0) {i->F |= 0b00000100;}
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error ldir(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->H; // addr
    i->F &= 0b11101001;
    i->F |= 0b00000100;
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    *(uint16_t *)inf[0] = i->E << 8; // addr
    *(uint16_t *)inf[0] |= i->D; // addr
    i->MState = 3;
    i->TCycle = 1;
    return SUCCESS;
  }  
  if (i->MState == 3) {
    increment16(&(i->D), &(i->E));
    increment16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    if (i->B != 0 && i->C == 0) {
      i->F &= 0b11111011;
      return nop(i, inf);
    }
    i->MState = 2;
    i->TCycle = 1;
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->H; // addr
    return SUCCESS;
  }
  return BAD_ARGUMENT;
}

enum Error ldd(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->H; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    *(uint16_t *)inf[0] = i->E << 8; // addr
    *(uint16_t *)inf[0] |= i->D; // addr
    i->MState = 3;
    i->TCycle = 1;
    return SUCCESS;
  }  
  if (i->MState == 3) {
    decrement16(&(i->D), &(i->E));
    decrement16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    i->F &= 0b11101001;
    if (i->B != 0 && i->C != 0) {i->F |= 0b00000100;}
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error lddr(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->H; // addr
    i->F &= 0b11101001;
    i->F |= 0b00000100;
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    *(uint16_t *)inf[0] = i->E << 8; // addr
    *(uint16_t *)inf[0] |= i->D; // addr
    i->MState = 3;
    i->TCycle = 1;
    return SUCCESS;
  }  
  if (i->MState == 3) {
    decrement16(&(i->D), &(i->E));
    decrement16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    if (i->B != 0 && i->C == 0) {
      i->F &= 0b11111011;
      return nop(i, inf);
    }
    i->MState = 2;
    i->TCycle = 1;
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->H; // addr
    return SUCCESS;
  }
  return BAD_ARGUMENT;
}

enum Error cpi(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->L; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    increment16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    uint8_t result = i->A - i->tmp;
    uint8_t carries = !getAddCarries(i->A, !(i->tmp)+1, 0);

    i->F &= 0b00000001;
    i->F |= 0b00000010;
    if (result & 0b10000000) {i->F |= 0b10000000;} // S flag
    if (result == 0) {i->F |= 0b01000000;} // Z flag
    if (carries & 0b00001000) {i->F |= 0b00010000;} // H flag
    if (i->B != 0 && i->C != 0){ i->F |= 0b00000100;} //P/V flag
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error cpir(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->L; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    increment16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    uint8_t result = i->A - i->tmp;
    uint8_t carries = !getAddCarries(i->A, !(i->tmp)+1, 0);

    i->F &= 0b00000001;
    i->F |= 0b00000110;
    if (result & 0b10000000) {i->F |= 0b10000000;} // S flag
    if (result == 0) {i->F |= 0b01000000;} // Z flag
    if (carries & 0b00001000) {i->F |= 0b00010000;} // H flag
    if (i->B == 0 && i->C == 0) {
      i->F &= 0b11111011;
      return nop(i, inf);
    }
    i->TCycle = 1;
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->L; // addr
  }
  return BAD_ARGUMENT;
}

enum Error cpd(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->L; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    decrement16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    uint8_t result = i->A - i->tmp;
    uint8_t carries = !getAddCarries(i->A, !(i->tmp)+1, 0);

    i->F &= 0b00000001;
    i->F |= 0b00000010;
    if (result & 0b10000000) {i->F |= 0b10000000;} // S flag
    if (result == 0) {i->F |= 0b01000000;} // Z flag
    if (carries & 0b00001000) {i->F |= 0b00010000;} // H flag
    if (i->B != 0 && i->C != 0){ i->F |= 0b00000100;} //P/V flag
    return nop(i, inf);
  }
  return BAD_ARGUMENT;
}

enum Error cpdr(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->L; // addr
    i->stateIterator = 0;
    return SUCCESS;
  }
  
  if (i->MState == 2) {
    decrement16(&(i->H), &(i->L));
    decrement16(&(i->B), &(i->C));

    uint8_t result = i->A - i->tmp;
    uint8_t carries = !getAddCarries(i->A, !(i->tmp)+1, 0);

    i->F &= 0b00000001;
    i->F |= 0b00000110;
    if (result & 0b10000000) {i->F |= 0b10000000;} // S flag
    if (result == 0) {i->F |= 0b01000000;} // Z flag
    if (carries & 0b00001000) {i->F |= 0b00010000;} // H flag
    if (i->B == 0 && i->C == 0) {
      i->F &= 0b11111011;
      return nop(i, inf);
    }
    i->TCycle = 1;
    *(uint16_t *)inf[0] = i->H << 8; // addr
    *(uint16_t *)inf[0] |= i->L; // addr
  }
  return BAD_ARGUMENT;
}
