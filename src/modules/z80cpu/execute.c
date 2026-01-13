#include "execute.h"
#include "execute_control.h"

enum Error execute(struct Instance *__restrict i, void **__restrict inf) {
  switch (i->state) {
  case HALT: return halt(i);
  case BAD:  return halt(i);
  default:   return SUCCESS;
  }
}
