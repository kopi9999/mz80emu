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
