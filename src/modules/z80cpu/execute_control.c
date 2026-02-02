#include "execute_control.h"

enum Error halt(struct Instance* __restrict i){
  i->halted = 1;
  return SUCCESS;
}
