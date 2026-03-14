#include "execute_control.h"

uint8_t pairity(uint8_t a) {
  uint8_t pairity = 0;
  for (uint8_t i = 0; i < 8; ++i) {
    pairity += a & 0b00000001;
    a = a >> 1;
  }
  return pairity;
}

enum Error halt(struct Instance* __restrict i, void** __restrict inf){
  i->halted = 1;
  i->PC--;
  return nop(i, inf);
}


enum Error nop(struct Instance* __restrict i, void** __restrict inf){
  i->MState = 1;
  i->TCycle = 1;
  i->currentPrefix = NO_PREFIX;
  i->currentOverride = NO_OVERRIDE;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}

enum Error daa(struct Instance* __restrict i, void** __restrict inf){
  switch(i->F){
    case 0b00000000:
      if ((i->A & 0b00001111) < 10 && ((i->A & 0b11110000) >> 4) < 10){
	break;
      }
      if ((i->A & 0b00001111) > 9 && ((i->A & 0b11110000) >> 4) < 9){
	i->A += 6;
	break;
      }
      if ((i->A & 0b00001111) < 10 && ((i->A & 0b11110000) >> 4) > 9){
	i->A += 0x60;
	i->F |= 0x00000001;
	break;
      }
      if ((i->A & 0b00001111) > 9 && ((i->A & 0b11110000) >> 4) > 8){
	i->A += 0x66;
	i->F |= 0x00000001;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00000001:
      if ((i->A & 0b00001111) < 10 && ((i->A & 0b11110000) >> 4) < 3){
	i->A += 0x60;
	i->F |= 0x00000001;
	break;
      }
      if ((i->A & 0b00001111) < 9 && ((i->A & 0b11110000) >> 4) < 3){
	i->A += 0x66;
	i->F |= 0x00000001;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00000010:
      if ((i->A & 0b00001111) < 10 && ((i->A & 0b11110000) >> 4) < 10){
	break;
      }
       if ((i->A & 0b00001111) > 9 && ((i->A & 0b11110000) >> 4) < 9){
	i->A += 6;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00000011:
      if ((i->A & 0b00001111) < 10 && ((i->A & 0b11110000) >> 4) < 3){
	i->A += 0x60;
	i->F |= 0x00000001;
	break;
      }
      if ((i->A & 0b00001111) > 9 && ((i->A & 0b11110000) >> 4) < 3){
	i->A += 0x66;
	i->F |= 0x00000001;
	break;
      }
      if ((i->A & 0b00001111) < 10 && ((i->A & 0b11110000) >> 4) > 6){
	i->A += 0xA0;
	i->F |= 0x00000001;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00010000:
      if ((i->A & 0b00001111) < 4 && ((i->A & 0b11110000) >> 4) < 10){
	i->A += 0x06;
	break;
      }
      if ((i->A & 0b00001111) < 4 && ((i->A & 0b11110000) >> 4) > 9){
	i->A += 0x66;
	i->F |= 0x00000001;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00010001:
      if ((i->A & 0b00001111) < 4 && ((i->A & 0b11110000) >> 4) < 4){
	i->A += 0x66;
	i->F |= 0x00000001;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00010010:
      if ((i->A & 0b00001111) < 4 && ((i->A & 0b11110000) >> 4) < 10){
	i->A += 0x06;
	break;
      }
      if ((i->A & 0b00001111) > 5 && ((i->A & 0b11110000) >> 4) < 9){
	i->A += 0xFA;
	break;
      }
      return BAD_ARGUMENT;
    case 0b00010011:
      if ((i->A & 0b00001111) < 4 && ((i->A & 0b11110000) >> 4) < 4){
	i->A += 0x66;
	i->F |= 0x00000001;
	break;
      }
      if (((i->A & 0b00001111) == 6 || (i->A & 0b00001111) == 7) && ((i->A & 0b11110000) >> 4) > 5){
	i->A += 0x9A;
	i->F |= 0x00000001;
	break;
      }
      return BAD_ARGUMENT;
  }
  uint8_t flags = i->F & 0b00010011;
  if (i->A & 0b10000000) {flags |= 0b10000000;} //S flag
  if (i->A == 0) {flags |= 0b01000000;} // Z flag
  if (pairity(i->A) % 2 == 0) {flags |= 0b00000100;}
  i->F = flags;
  return nop(i, inf);
}

enum Error cpl(struct Instance* __restrict i, void** __restrict inf){
  i->A = !i->A;
  i->F |= 0b00010010;
  return nop(i, inf);
}

enum Error ccf(struct Instance* __restrict i, void** __restrict inf){
  i->F ^= 0b00000001;
  i->F &= 0b11111101;
  return nop(i, inf);
}

enum Error scf(struct Instance* __restrict i, void** __restrict inf){
  i->F |= 0b00000001;
  i->F &= 0b11101101;
  return nop(i, inf);
}
