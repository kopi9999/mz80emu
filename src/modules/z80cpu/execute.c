#include "execute.h"
#include "execute_control.h"
#include "execute_load.h"
#include "execute_exchange.h"
#include "execute_jump.h"
#include "execute_arit.h"
#include "execute_rotate.h"
#include "execute_bsr.h"

enum Error ed_prefix(struct Instance *__restrict i, void **__restrict inf) {
  i->currentPrefix = ED_PREFIX;
  i->MState = 1;
  i->TCycle = 1;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}

enum Error cb_prefix(struct Instance *__restrict i, void **__restrict inf) {
  i->currentPrefix = CB_PREFIX;
  i->MState = 1;
  i->TCycle = 1;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}

enum Error ix_override(struct Instance *__restrict i, void **__restrict inf) {
  i->currentOverride = IX_OVERRIDE;
  i->MState = 1;
  i->TCycle = 1;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}

enum Error iy_override(struct Instance *__restrict i, void **__restrict inf) {
  i->currentOverride = IY_OVERRIDE;
  i->MState = 1;
  i->TCycle = 1;
  *(uint8_t*) inf[2] = 1; // m1
  *(uint16_t*) inf[0] = i->PC;
  return SUCCESS;
}

enum Error execute_up(struct Instance *__restrict i, void **__restrict inf) {
  if (i->halted) {return halt(i, inf);}
  switch (i->state) {
  case BAD:       return halt(i, inf);
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
    // exchange, block transfer and search group
  case EX_DE_HL:  return ex_de_hl(i, inf); 
  case EX_AF_AF:  return ex_af_af(i, inf); 
  case EXX:       return exx(i, inf); 
  case EX_$SP$_HL: return ex_$sp$_hl(i, inf); 
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
  case CP_R:      return cp_r(i, inf); 
  case CP_N:      return cp_n(i, inf); 
  case CP_$HL$:   return cp_$hl$(i, inf); 
  case INC_R:     return inc_r(i, inf); 
  case INC_$HL$:  return inc_$hl$(i, inf); 
  case DEC_R:     return dec_r(i, inf); 
  case DEC_$HL$:  return dec_$hl$(i, inf); 
    // control group
  case HALT:      return halt(i, inf);
  case NOP:       return nop(i, inf);
  case DAA:       return daa(i, inf);
  case CPL:       return cpl(i, inf);
  case CCF:       return ccf(i, inf);
  case SCF:       return scf(i, inf);
    // rotate and shift group
  case RLCA:      return rlca(i, inf);
  case RLA:       return rla(i, inf);
  case RRA:       return rra(i, inf);
  case RLC_R:     return rlc_r(i, inf); // CB prefix
  case RLC_$HL$:  return rlc_$hl$(i, inf); // CB prefix
  case RL_R:      return rl_r(i, inf); // CB prefix
  case RL_$HL$:   return rl_$hl$(i, inf); // CB prefix
  case RRC_R:     return rrc_r(i, inf); // CB prefix
  case RRC_$HL$:  return rrc_$hl$(i, inf); // CB prefix
  case RR_R:      return rr_r(i, inf); // CB prefix
  case RR_$HL$:   return rr_$hl$(i, inf); // CB prefix
  case SLA_R:     return sla_r(i, inf); // CB prefix
  case SLA_$HL$:  return sla_$hl$(i, inf); // CB prefix
  case SRA_R:     return sra_r(i, inf); // CB prefix
  case SRA_$HL$:  return sra_$hl$(i, inf); // CB prefix
  case SRL_R:     return srl_r(i, inf); // CB prefix
  case SRL_$HL$:  return srl_$hl$(i, inf); // CB prefix
  case RLD:       return rld(i, inf); // ED prefix
  case RRD:       return rrd(i, inf); // ED prefix
    // bit, set, and reset group
  case BIT_B_R:   return bit_b_r(i, inf); // CB group
    // jump group
  case JP_NN:     return jp_nn(i, inf);  
  case JP_CC_NN:  return jp_cc_nn(i, inf);  
  case JR_E:      return jr_e(i, inf);  
  case JR_C_E:    return jr_c_e(i, inf);
  case JR_NC_E:   return jr_nc_e(i, inf);
  case JR_Z_E:    return jr_z_e(i, inf);
  case JR_NZ_E:   return jr_nz_e(i, inf);
  case JP_$HL$:   return jp_$hl$(i, inf);
    // prefixes
  case ED_prefix: return ed_prefix(i, inf);
  case CB_prefix: return cb_prefix(i, inf);
  case IX_override: return ix_override(i, inf);
  case IY_override: return iy_override(i, inf);
    
  default:        return halt(i, inf);
  }
}

enum Error execute_down(struct Instance *__restrict i, void **__restrict inf) {
  if (i->skipTick) {return SUCCESS;}
  switch (i->state) {
  case HALT: return halt(i, inf);
  case BAD:  return halt(i, inf);
  default:   return halt(i, inf);
  }
}

