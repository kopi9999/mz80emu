#include "execute_control.h"

enum Error halt(struct Instance* __restrict i, void** __restrict inf){
  i->halted = 1;
  i->PC--;
  return nop(i, inf);
}


enum Error nop(struct Instance* __restrict i, void** __restrict inf){
  i->MState = 1;
  i->TCycle = 1;
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
  return nop(i, inf);
}
