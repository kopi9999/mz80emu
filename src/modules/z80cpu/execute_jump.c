#include "execute_load.h"
#include "execute_control.h"

enum Error jp_nn(struct Instance*__restrict i, void**__restrict inf) {
  if (i->MState == 1) {
    i->MState = 2;
    i->TCycle = 1;
    *(uint8_t*) inf[2] = 0; //m1
    *(uint16_t*) inf[0] = i->PC; //addr
    i->stateIterator = 0;
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
}
