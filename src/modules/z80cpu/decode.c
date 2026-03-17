#include "decode.h"

enum Instruction decodeInstruction(struct Instance* __restrict  i) 
{
    if (i->instruction & 0b10000000) {
        if (i->instruction & 0b01000000) {
            switch (i->instruction & 0b00000111){
                case 0: return RET_CC;
                case 1: 
                    if (i->instruction & 0b00001000) {
                       switch(i->instruction & 0b00110000){
                            case 0b00000000: return RET;
                            case 0b00010000: return EXX;
                            case 0b00100000: return JP_$HL$;
                            case 0b00110000: return LD_SP_HL;
                        } 
                    }  else { return POP_QQ;}
                case 2: return JP_CC_NN;
                case 3:
                    if (i->instruction & 0b00001000) {
                       switch(i->instruction & 0b00110000){
                            case 0b00000000: return CB_prefix;
                            case 0b00010000: return IN_A_$N$;
                            case 0b00100000: return EX_DE_HL ;
                            case 0b00110000: return EI;
                        } 
                    }  else { return JP_NN;}
                case 4: return CALL_CC_NN;
                case 5: 
                    if (i->instruction & 0b00001000) {
                       switch(i->instruction & 0b00110000){
                            case 0b00000000: return CALL_NN;
                            case 0b00010000: return IX_override;
                            case 0b00100000: return ED_prefix;
                            case 0b00110000: return IY_override;
                        } 
                    }  else { return PUSH_QQ;}
                case 6: 
                    switch (i->instruction & 0b00111000){
                        case 0b00000000: return ADD_A_N;
                        case 0b00001000: return ADC_A_N;
                        case 0b00010000: return SUB_N;
                        case 0b00011000: return SBC_A_N;
                        case 0b00100000: return AND_N;
                        case 0b00101000: return XOR_N;
                        case 0b00110000: return OR_S;
                        case 0b00111000: return CP_N;
                    }
                case 7: return RST_P;
            }
        }
        else{
            switch (i->instruction & 0b00111000) {
                case 0b00000000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return ADD_A_$HL$;}
                    else {return ADD_A_R;}
                case 0b00001000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return ADC_A_$HL$;}
                    else {return ADC_A_R;}
                case 0b00010000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SUB_$HL$;}
                    else {return SUB_R;}
                case 0b00011000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SBC_A_$HL$;}
                    else {return SBC_A_R;}
                case 0b00100000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return AND_$HL$;}
                    else {return AND_R;}
                case 0b00101000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return OR_$HL$;}
                    else {return OR_R;}
                case 0b00110000:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return XOR_$HL$;}
                    else {return XOR_R;}
                case 0b00111000: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return CP_$HL$;}
                    else {return CP_R;}
            }
        }
    }
    else {
        if (i->instruction & 0b01000000){ // 01xxxxxx
            if ((i->instruction & 0b00111000) == UNDEFINED * 8){
                if ((i->instruction & 0b00000111) == UNDEFINED) {return HALT;}
                else {return LD_$HL$_R;}
            } 
            else if ((i->instruction & 0b00000111) == UNDEFINED){return LD_R_$HL$;} 
            else {
	      i->registerOut = i->instruction & 0b00000111;
	      i->registerIn = (i->instruction & 0b00111000) >> 3;
              return LD_R_Rp;
	    }
        }
        else { //00xxxxxx
            switch (i->instruction & 0b00000111) {
                case 0: //00xxx000
                    switch (i->instruction & 0b00111000){
                        case 0b00000000: return NOP;
                        case 0b00001000: return EX_AF_AF;
                        case 0b00010000: return DJNZ_E;
                        case 0b00011000: return JR_E;
                        case 0b00100000: return JR_NZ_E;
                        case 0b00101000: return JR_Z_E;
                        case 0b00110000: return JR_NC_E;
                        case 0b00111000: return JR_C_E;
                    }
                case 1: //00xxx001
                    if (i->instruction & 0b00001000) { return ADD_HL_SS; }
                    else { return LD_DD_NN; }
                case 2: //00xxx010
                    if (i->instruction & 0b00001000) {
                        switch (i->instruction & 0b00110000) {
                            case 0b00000000: return LD_A_$BC$;
                            case 0b00010000: return LD_A_$DE$;
                            case 0b00100000: return LD_HL_$NN$;
                            case 0b00110000: return LD_A_$NN$;
                        }
                    }
                    else {
                        switch (i -> instruction & 0b00110000) {
                            case 0b00000000: return LD_$BC$_A;
                            case 0b00010000: return LD_$DE$_A;
                            case 0b00100000: return LD_$NN$_HL;
                            case 0b00110000: return LD_$NN$_A;
                        }
                    }
                case 3: //00xxx011
                    if (i->instruction & 0b00001000) {return DEC_SS;}
                    else {return INC_SS;}
                case 4: //00xxx100
                    if ((i->instruction & 0b00111000) == UNDEFINED * 8) {return INC_$HL$;}
                    else {return INC_R;}
                case 5: //00xxx101
                    if ((i->instruction & 0b00111000) == UNDEFINED * 8) {return DEC_$HL$;}
                    else {return DEC_R;}
                case 6: //00xxx110
                    if ((i->instruction & 0b00111000) == UNDEFINED * 8) {return LD_$HL$_N;}
                    else {return LD_R_N;}
                case 7: //00xxx111
                    switch (i->instruction & 0b00111000) {
                        case 0b00000000: return RLCA;
                        case 0b00001000: return RRCA;
                        case 0b00010000: return RLA;
                        case 0b00011000: return RRA;
                        case 0b00100000: return DAA;
                        case 0b00101000: return CPL;
                        case 0b00110000: return SCF;
                        case 0b00111000: return CCF;
                    }
            }
        }
    }

    return 0;
}

enum Instruction decodeInstruction_CB (struct Instance* __restrict i) {
    switch(i->instruction & 0b11000000) {
        case 0: 
            switch(i->instruction & 0b00111000){
                case 0: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return RLC_$HL$;}
                    else {return RLC_R;}
                case 1:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return RRC_$HL$;}
                    else {return RRC_R;}
                case 2:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return RL_$HL$;}
                    else {return RL_R;}
                case 3:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return RR_$HL$;}
                    else {return RR_R;}
                case 4:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SLA_$HL$;}
                    else {return SLA_R;}
                case 5:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SRA_$HL$;}
                    else {return SRA_R;}
                case 6: return BAD;
                case 7:
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SRL_$HL$;}
                    else {return SRL_R;}
            }
        case 1:
            if((i->instruction & 0b00000111) == UNDEFINED){return BIT_B_$HL$;}
            else {return BIT_B_R;}
        case 2: 
            if((i->instruction & 0b00000111) == UNDEFINED){return RES_B_$HL$;}
            else {return RES_B_RN;}
        case 3:
            if((i->instruction & 0b00000111) == UNDEFINED){return SET_B_$HL$;}
            else {return SET_B_R;}
    }
    return 0;
}
enum Instruction decodeInstruction_ED (struct Instance* __restrict i) {
   if (((i->instruction & 0b11000000) >> 6) == 1) {
        switch (i->instruction & 0b00000111){
            case 0: return IN_R_$C$;
            case 1: 
                if ((i->instruction & 0b00111000) == UNDEFINED) {return BAD;}
                else {return OUT_$C$_R;}
            case 2:
                if (i->instruction & 0b00001000) {return ADC_HL_SS;} 
                else {return SBC_HL_SS;}
            case 3:
                if (i->instruction & 0b00001000) {return LD_DD_$NN$;} 
                else {return LD_$NN$_DD;}
            case 4:
                if (i->instruction == 0b01000100) {return NEG;} break;
            case 5:
                if (i->instruction == 0b01000101) {return RETN;}
                else if(i->instruction == 0b01001101) {return RETI;}
                break;
            case 6:
                if (i->instruction & 0b00100000) {return BAD;}
                else if (i->instruction & 0b00001000) {return BAD;}
                else {return IM_N;}
     	    case 7: switch((i->instruction & 0b00111000) >> 3) {
                case 0: return LD_I_A;
                case 1: return LD_R_A;
                case 2: return LD_A_I;
                case 3: return LD_A_R;
                case 4: return RRD;
                case 5: return RLD;
                case 6: return BAD;
                case 7: return BAD;
            }
        }
    } else if (((i->instruction & 0b11100000) >> 5) == 5) {
        switch (i->instruction & 0b00000111) {
            case 0:
	        switch ((i->instruction & 0b00011000) >> 3) {
                    case 0: return LDI;
                    case 1: return LDD;
                    case 2: return LDIR;
                    case 3: return LDDR;
                }
            case 1:
	        switch ((i->instruction & 0b00011000) >> 3) {
                    case 0: return CPI;
                    case 1: return CPD;
                    case 2: return CPIR;
                    case 3: return CPDR;
                }
            case 2:
	        switch ((i->instruction & 0b00011000) >> 3) {
                    case 0: return INI;
                    case 1: return IND;
                    case 2: return INIR;
                    case 3: return INDR;
                }
            case 3:
	        switch ((i->instruction & 0b00011000) >> 3) {
                    case 0: return OUTI;
                    case 1: return OUTD;
                    case 2: return OTIR;
                    case 3: return OTDR;
                }
        }
    }
    return BAD;
}


enum Instruction decodeInstruction_IX (struct Instance* __restrict i) {
  return BAD; //not implemented
}

enum Instruction decodeInstruction_IY (struct Instance* __restrict i) {
  return BAD; //not implemented
}
