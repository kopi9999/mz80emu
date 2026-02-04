#include "execute_control.h"

enum Error halt(struct Instance* __restrict i, void** __restrict inf){
  i->halted = 1;
  i->MState = 1;
  i->TCycle = 1;
  i->PC--;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}


enum Error nop(struct Instance* __restrict i, void** __restrict inf){
  i->MState = 1;
  i->TCycle = 1;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}
