#include "execute_arit16.h"
#include "execute_control.h"

enum Error add_hl_ss(struct Instance *__restrict i, void **__restrict inf) {
  uint8_t carryL, carryH;
  uint16_t tmp;
  if (i->currentOverride == IX_OVERRIDE) {
    switch ((i->instruction & 0b00110000) >> 4) {
      case BC:
	carryL = getAddCarries(i->IX & 0x00FF, i->C, 0);
	carryH = getAddCarries(i->IX >> 8, i->B, carryL >> 7);
	i->IX += (i->B << 8) | i->C; 
	break;
      case DE:
	carryL = getAddCarries(i->IX & 0x00FF, i->E, 0);
	carryH = getAddCarries(i->IX >> 8, i->D, carryL >> 7);
	i->IX += (i->D << 8) | i->E; 
	break;
      case HL:
	carryL = getAddCarries(i->IX & 0x00FF, i->L, 0);
	carryH = getAddCarries(i->IX >> 8, i->H, carryL >> 7);
	i->IX += (i->H << 8) | i->L; 
	break;
      case SP:
	carryL = getAddCarries(i->IX & 0x00FF, i->SP & 0x00FF, 0);
	carryH = getAddCarries(i->IX >> 8, i->SP >> 8, carryL >> 7);
	i->IX += i->SP; 
	break;
    }
  }
  else if (i->currentOverride == IY_OVERRIDE) {
    switch ((i->instruction & 0b00110000) >> 4) {
      case BC:
	carryL = getAddCarries(i->IY & 0x00FF, i->C, 0);
	carryH = getAddCarries(i->IY >> 8, i->B, carryL >> 7);
	i->IY += (i->B << 8) | i->C; 
	break;
      case DE:
	carryL = getAddCarries(i->IY & 0x00FF, i->E, 0);
	carryH = getAddCarries(i->IY >> 8, i->D, carryL >> 7);
	i->IY += (i->D << 8) | i->E; 
	break;
      case HL:
	carryL = getAddCarries(i->IY & 0x00FF, i->L, 0);
	carryH = getAddCarries(i->IY >> 8, i->H, carryL >> 7);
	i->IY += (i->H << 8) | i->L; 
	break;
      case SP:
	carryL = getAddCarries(i->IY & 0x00FF, i->SP & 0x00FF, 0);
	carryH = getAddCarries(i->IY >> 8, i->SP >> 8, carryL >> 7);
	i->IY += i->SP; 
	break;
    }
  }
  else {
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
  }
  i->F &= 0b11101100;

  if (carryH & 0b00010000) {i->F |= 0b00010000;} // H flag
  if (carryH & 0b10000000) {i->F |= 0b00000001;} // P/V flag
  return nop(i, inf);
}

enum Error adc_hl_ss(struct Instance *__restrict i, void **__restrict inf) {
  uint8_t carryL, carryH;
  switch ((i->instruction & 0b00110000) >> 4) {
    case BC:
      carryL = getAddCarries(i->L, i->C, i->F & 0b00000001);
      carryH = getAddCarries(i->H, i->B, carryL >> 7);
      i->L += i->C + i->F & 0b00000001;
      i->H += i->B + (carryL >> 7);
      break;
    case DE:
      carryL = getAddCarries(i->L, i->E, i->F & 0b00000001);
      carryH = getAddCarries(i->H, i->D, carryL >> 7);
      i->L += i->E + i->F & 0b00000001;
      i->H += i->D + (carryL >> 7);
      break;
    case HL:
      carryL = getAddCarries(i->L, i->L, i->F & 0b00000001);
      carryH = getAddCarries(i->H, i->H, carryL >> 7);
      i->L += i->L + i->F & 0b00000001;
      i->H += i->H + (carryL >> 7);
      break;
    case SP:
      carryL = getAddCarries(i->L, i->SP & 0x00FF, i->F & 0b00000001);
      carryH = getAddCarries(i->H, i->SP >> 8, carryL >> 7);
      i->L += (i->SP & 0x00FF) + i->F & 0b00000001;
      i->H += (i->SP >> 8) + (carryL >> 7);
      break;
  }
  i->F &= 0b11101100;

  if (carryH & 0b00010000) {i->F |= 0b00010000;} // H flag
  if (carryH & 0b10000000) {i->F |= 0b00000001;} // P/V flag
  return nop(i, inf);
}

enum Error sbc_hl_ss(struct Instance *__restrict i, void **__restrict inf) {
  uint8_t borrowL, borrowH;
  switch ((i->instruction & 0b00110000) >> 4) {
    case BC:
      borrowL = getAddCarries(i->L, i->C, i->F & 0b00000001);
      borrowH = getAddCarries(i->H, i->B, borrowL >> 7);
      i->L -= i->C - i->F & 0b00000001;
      i->H -= i->B - (borrowL >> 7);
      break;
    case DE:
      borrowL = getAddCarries(i->L, i->E, i->F & 0b00000001);
      borrowH = getAddCarries(i->H, i->D, borrowL >> 7);
      i->L -= i->E - i->F & 0b00000001;
      i->H -= i->D - (borrowL >> 7);
      break;
    case HL:
      borrowL = getAddCarries(i->L, i->L, i->F & 0b00000001);
      borrowH = getAddCarries(i->H, i->H, borrowL >> 7);
      i->L -= i->L - i->F & 0b00000001;
      i->H -= i->H - (borrowL >> 7);
      break;
    case SP:
      borrowL = getAddCarries(i->L, i->SP & 0x00FF, i->F & 0b00000001);
      borrowH = getAddCarries(i->H, i->SP >> 8, borrowL >> 7);
      i->L -= (i->SP & 0x00FF) - i->F & 0b00000001;
      i->H -= (i->SP >> 8) - (borrowL >> 7);
      break;
  }
  i->F &= 0b11101100;

  if (borrowH & 0b00010000) {i->F |= 0b00010000;} // H flag
  if (borrowH & 0b10000000) {i->F |= 0b00000001;} // P/V flag
  return nop(i, inf);
}


enum Error inc_ss(struct Instance *__restrict i, void **__restrict inf) {
  if (i->currentOverride && i->instruction != 0x23) {return BAD_ARGUMENT;}

  uint8_t carry;
  if (i->currentOverride == IX_OVERRIDE) {i->IX++;}
  else if (i->currentOverride == IY_OVERRIDE) {i->IY++;}
  else {
    switch ((i->instruction & 0b00110000) >> 4) {
      case BC: increment16(&i->B, &i->C); break;
      case DE: increment16(&i->D, &i->E); break;
      case HL: increment16(&i->H, &i->L); break;
      case SP: i->SP++; break;
    }
  }
  return nop(i, inf);
}


enum Error dec_ss(struct Instance *__restrict i, void **__restrict inf) {
  if (i->currentOverride && i->instruction != 0x2B) {return BAD_ARGUMENT;}

  uint8_t borrow;
  if (i->currentOverride == IX_OVERRIDE) {i->IX--;}
  else if (i->currentOverride == IY_OVERRIDE) {i->IY--;}
  else {
    switch ((i->instruction & 0b00110000) >> 4) {
      case BC: decrement16(&i->B, &i->C); break;
      case DE: decrement16(&i->D, &i->E); break;
      case HL: decrement16(&i->H, &i->L); break;
      case SP: i->SP--; break;
    }
  }
  return nop(i, inf);
}
