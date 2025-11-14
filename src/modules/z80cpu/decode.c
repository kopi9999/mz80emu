#include "decode.h"

enum CpuState decodeInstruction(struct Instance* __restrict  i) 
{
    if (i->instruction & 0b10000000) {
        if (i->instruction & 0b01000000) {
            switch (i->instruction & 0b00000111){
                case 0: return RET_CC;
                case 1: 
                    if (i->instruction & 0b00001000) {
                       switch(i->instruction & 0b00110000){
                            case 0: return RET;
                            case 1: return EXX;
                            case 2: return JP_$HL$;
                            case 3: return LD_SP_HL;
                        } 
                    }  else { return POP_QQ;}
                case 2: return JP_CC_NN;
                case 3:
                    if (i->instruction & 0b00001000) {
                       switch(i->instruction & 0b00110000){
                            case 0: return CB_prefix;
                            case 1: return IN_A_$N$;
                            case 2: return EX_DE_HL ;
                            case 3: return EI;
                        } 
                    }  else { return JP_NN;}
                case 4: return CALL_CC_NN;
                case 5: 
                    if (i->instruction & 0b00001000) {
                       switch(i->instruction & 0b00110000){
                            case 0: return CALL_NN;
                            case 1: return IX_override;
                            case 2: return ED_prefix;
                            case 3: return IY_override;
                        } 
                    }  else { return PUSH_QQ;}
                case 6: 
                    switch (i->instruction & 0b00111000){
                        case 0: return ADD_A_N;
                        case 1: return ADC_A_N;
                        case 2: return SUB_N;
                        case 3: return SBC_A_N;
                        case 4: return AND_N;
                        case 5: return XOR_N;
                        case 6: return OR_S;
                        case 7: return CP_N;
                    }
                case 7: return RST_P;
            }
        }
        else{
            switch (i->instruction & 0b00111000) {
                case 0: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return ADD_A_$HL$;}
                    else {return ADD_A_R;}
                case 1: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return ADC_A_$HL$;}
                    else {return ADC_A_R;}
                case 2: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SUB_$HL$;}
                    else {return SUB_R;}
                case 3: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return SBC_A_$HL$;}
                    else {return SBC_A_R;}
                case 4: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return AND_$HL$;}
                    else {return AND_R;}
                case 5: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return OR_A_$HL$;}
                    else {return OR_A_R;}
                case 6: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return XOR_$HL$;}
                    else {return XOR_R;}
                case 7: 
                    if ((i->instruction & 0b00000111) == UNDEFINED) {return CP_$HL$;}
                    else {return CP_R;}
            }
        }
    }
    else {
        if (i->instruction & 0b01000000){ // 01xxxxxx
            if ((i->instruction & 0b00111000) == UNDEFINED){
                if ((i->instruction & 0b00000111) == UNDEFINED) {return HALT;}
                else {return LD_$HL$_R;}
            } 
            else if ((i->instruction & 0b00000111) == UNDEFINED){return LD_R_$HL$;} 
            else {return LD_R_Rp;}
        }
        else { //00xxxxxx
            switch (i->instruction & 0b00000111) {
                case 0: //00xxx000
                    switch (i->instruction & 0b00111000){
                        case 0: return NOP;
                        case 1: return EX_AF_AF;
                        case 2: return DJNZ_E;
                        case 3: return JR_E;
                        case 4: return JR_NZ_E;
                        case 5: return JR_Z_E;
                        case 6: return JR_NC_E;
                        case 7: return JR_C_E;
                    }
                case 1: //00xxx001
                    if (i->instruction & 0b00001000) { return ADD_HL_SS; }
                    else { return LD_DD_NN; }
                case 2: //00xxx010
                    if (i->instruction & 0b00001000) {
                        switch (i->instruction & 0b00110000) {
                            case 0: return LD_A_$BC$;
                            case 1: return LD_A_$DE$;
                            case 2: return LD_HL_$NN$;
                            case 3: return LD_A_$NN$;
                        }
                    }
                    else {
                        switch (i -> instruction & 0b00110000) {
                            case 0: return LD_$BC$_A;
                            case 1: return LD_$DE$_A;
                            case 2: return LD_$NN$_HL;
                            case 3: return LD_$NN$_A;
                        }
                    }
                case 3: //00xxx011
                    if (i->instruction & 0b00001000) {return DEC_SS;}
                    else {return INC_SS;}
                case 4: //00xxx100
                    if ((i->instruction & 0b00111000) == UNDEFINED) {return INC_$HL$;}
                    else {return INC_R;}
                case 5: //00xxx101
                    if ((i->instruction & 0b00111000) == UNDEFINED) {return DEC_$HL$;}
                    else {return DEC_Rp;}
                case 6: //00xxx110
                    if ((i->instruction & 0b00111000) == UNDEFINED) {return LD_$HL$_N;}
                    else {return LD_R_N;}
                case 7: //00xxx111
                    switch (i->instruction & 0b00111000) {
                        case 0: return RLCA;
                        case 1: return RRCA;
                        case 2: return RLA;
                        case 3: return RRA;
                        case 4: return DAA;
                        case 5: return CPL;
                        case 6: return SCF;
                        case 7: return CCF;
                    }
            }
        }
    }

    return RESET;
}
