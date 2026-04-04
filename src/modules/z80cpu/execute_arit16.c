#include "execute_arit16.h"
#include "execute_control.h"

enum Error add_hl_ss(struct Instance *__restrict i, void **__restrict inf) {
  uint8_t carryL, carryH;
  switch ((i->instruction & 0b00110000) >> 4) {
    case BC:
      carryL = getAddCarries(i->L, i->C, 0);
      carryH = getAddCarries(i->H, i->B, carryL >> 7);
      i->L += i->C;
      i->H += i->B + (carryL >> 7);
      break;
    case DE:
      carryL = getAddCarries(i->L, i->E, 0);
      carryH = getAddCarries(i->H, i->D, carryL >> 7);
      i->L += i->E;
      i->H += i->D + (carryL >> 7);
      break;
    case HL:
      carryL = getAddCarries(i->L, i->L, 0);
      carryH = getAddCarries(i->H, i->H, carryL >> 7);
      i->L += i->L;
      i->H += i->H + (carryL >> 7);
      break;
    case SP:
      carryL = getAddCarries(i->L, i->SP & 0x00FF, 0);
      carryH = getAddCarries(i->H, i->SP >> 8, carryL >> 7);
      i->L += i->SP & 0x00FF;
      i->H += (i->SP >> 8) + (carryL >> 7);
      break;
  }
  i->F &= 0b11101100;

  if (carryH & 0b00010000) {i->F |= 0b00010000;} // H flag
  if (carryH & 0b10000000) {i->F |= 0b00000001;} // P/V flag
  return nop(i, inf);
}
