#include "execute.h"
#include "execute_control.h"
#include "execute_load.h"
#include "execute_jump.h"
#include "execute_arit.h"

enum Error execute_up(struct Instance *__restrict i, void **__restrict inf) {
  if (i->halted) {return halt(i, inf);}
  switch (i->state) {
  case HALT:      return halt(i, inf);
  case BAD:       return halt(i, inf);
  case NOP:       return nop(i, inf);
    // 8bit load group
  case LD_R_Rp:   return ld_r_rp(i, inf);
  case LD_R_$HL$: return ld_r_$hl$(i, inf);
  case LD_R_N:    return ld_r_n(i, inf);
  case LD_$HL$_R: return ld_$hl$_r(i, inf);
  case LD_A_$BC$: return ld_a_$bc$(i, inf);
  case LD_A_$DE$: return ld_a_$de$(i, inf);
  case LD_A_$NN$: return ld_a_$nn$(i, inf);
  case LD_$BC$_A: return ld_$bc$_a(i, inf);
  case LD_$DE$_A: return ld_$de$_a(i, inf);
  case LD_$NN$_A: return ld_$nn$_a(i, inf);
    // 8bit arithmetic operation
  case ADD_A_R:   return add_a_r(i, inf); 
  case ADD_A_N:   return add_a_n(i, inf); 
  case ADD_A_$HL$:return add_a_$hl$(i, inf); 
  case ADC_A_R:   return adc_a_r(i, inf); 
  case ADC_A_N:   return adc_a_n(i, inf); 
  case ADC_A_$HL$:return adc_a_$hl$(i, inf); 
  case SUB_R:     return sub_r(i, inf); 
  case SUB_N:     return sub_n(i, inf); 
  case SUB_$HL$:  return sub_$hl$(i, inf); 
  case SBC_A_R:   return sbc_a_r(i, inf); 
  case SBC_A_N:   return sbc_a_n(i, inf); 
  case SBC_A_$HL$:return sbc_a_$hl$(i, inf); 
  case AND_R:     return and_r(i, inf); 
  case AND_N:     return and_n(i, inf); 
  case AND_$HL$:  return and_$hl$(i, inf); 
  case OR_R:      return or_r(i, inf); 
  case OR_N:      return or_n(i, inf); 
  case OR_$HL$:   return or_$hl$(i, inf); 
  case XOR_R:     return xor_r(i, inf); 
  case XOR_N:     return xor_n(i, inf); 
  case XOR_$HL$:  return xor_$hl$(i, inf); 
    // jump group
  case JP_NN:     return jp_nn(i, inf);  
    
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
