#include "decode.h"

enum CpuState decodeInstruction(struct Instance* __restrict  i) 
{
    if (i->instruction & 0b10000000) {
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
                        case 4: return JR_NZ_E
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
