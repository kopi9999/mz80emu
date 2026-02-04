#include "execute.h"
#include "execute_control.h"

enum Error execute_up(struct Instance *__restrict i, void **__restrict inf) {
  switch (i->state) {
  case HALT: return halt(i);
  case BAD:  return halt(i);
  case NOP:  return nop(i, inf);
  default:   return halt(i);
  }
}

enum Error execute_down(struct Instance *__restrict i, void **__restrict inf) {
  switch (i->state) {
  case HALT: return halt(i);
  case BAD:  return halt(i);
  default:   return halt(i);
  }
}
