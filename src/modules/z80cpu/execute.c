#include "execute.h"
#include "execute_control.h"
#include "execute_load.h"

enum Error execute_up(struct Instance *__restrict i, void **__restrict inf) {
  if (i->halted) {return halt(i, inf);}
  switch (i->state) {
  case HALT:      return halt(i, inf);
  case BAD:       return halt(i, inf);
  case NOP:       return nop(i, inf);
  case LD_R_Rp:   return ld_r_rp(i, inf);
  case LD_R_$HL$: return ld_r_$hl$(i, inf);
  case LD_R_N:    return ld_r_n(i, inf);
  case LD_$HL$_R: return ld_$hl$_r(i, inf);
  default:        return halt(i, inf);
  }
}

enum Error execute_down(struct Instance *__restrict i, void **__restrict inf) {
  switch (i->state) {
  case HALT: return halt(i, inf);
  case BAD:  return halt(i, inf);
  default:   return halt(i, inf);
  }
}
