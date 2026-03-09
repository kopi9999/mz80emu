#include "execute_arit16.h"
#include "execute_control.h"

enum Error add_hl_ss(struct Instance *__restrict i, void **__restrict inf) {
  switch ((i->instruction & 0b00110000) >> 4) {
  case BC: i->H = i->B; i->L = i->C; break;
    case DE: i->H = i->D; i->L = i->E; break;
    case HL: break;
    case SP: i->H = i->SP >> 8; i->L = i->SP & 0x00FF; break;
  }
  return nop(i, inf);
}
