#ifndef TESTDLL
#define TESTDLL

#include <stdio.h>
#include <stdlib.h>

#include "../moduleInternal.h"

enum CpuState {
    RESET,
    LOAD,
    
    LD_R_Rp,
    LD_R_N,
    LD_R_$HL$,
    LD_R_$IX_plus_D$,
    LD_R_$IY_plus_D$,
    LD_$HL$_R,
    LD_$IX_plus_D$_R,
    LD_$IY_plus_D$_R,
    LD_$HL$_N,
    LD_$IX_plus_D$_N,
    LD_$IY_plus_D$_N,
    LD_A_$BC$,
    LD_A_$DE$,
    LD_A_$NN$,
    LD_$BC$_A,
    LD_$DE$_A,
    LD_$NN$_A,
    LD_A_I,
    LD_A_R,
    LD_I_A,
    LD_R_A,
    LD_DD_NN,
    LD_IX_NN,
    LD_IY_NN,
    LD_HL_$NN$,
    LD_DD_$NN$,
    LD_IX_$NN$,
    LD_IY_$NN$,
    LD_$NN$_HL,
    LD_$NN$_DD,
    LD_$NN$_IX,
    LD_$NN$_IY,
    LD_SP_HL,
    LD_SP_IX,
    LD_SP_IY,

    POP_QQ,
    POP_IX,
    POP_IY,
    EX_DE_HL,
    EX_AF_AF,
    EXX,
    EX_$SP$_HL,
    EX_$SP$_IX,
    EX_$SP$_IY,

    LDI,
    LDIR,
    LDD,
    LDDR,
    CPI,
    CPIR,
    CPD,
    CPDR,

    ADD_A_R,
    ADD_A_N,
    ADD_A_$HL$,
    ADD_A_$IX_plus_D$,
    ADD_A_$IY_plus_D$,

    ADC_A_R,
    ADC_A_N,
    ADC_A_$HL$,
    ADC_A_$IX_plus_D$,
    ADC_A_$IY_plus_D$,

    SUB_A_R,
    SUB_A_N,
    SUB_A_$HL$,
    SUB_A_$IX_plus_D$,
    SUB_A_$IY_plus_D$,

    SBC_A_R,
    SBC_A_N,
    SBC_A_$HL$,
    SBC_A_$IX_plus_D$,
    SBC_A_$IY_plus_D$,

    AND_A_R,
    AND_A_N,
    AND_A_$HL$,
    AND_A_$IX_plus_D$,
    AND_A_$IY_plus_D$,

    OR_A_R,
    OR_A_N,
    OR_A_$HL$,
    OR_A_$IX_plus_D$,
    OR_A_$IY_plus_D$,

    XOR_A_R,
    XOR_A_N,
    XOR_A_$HL$,
    XOR_A_$IX_plus_D$,
    XOR_A_$IY_plus_D$,

    CP_A_R,
    CP_A_N,
    CP_A_$HL$,
    CP_A_$IX_plus_D$,
    CP_A_$IY_plus_D$,

    AND_S,
    OR_S,
    XOR_S,
    CP_S,
    INC_R,
    INC_$HL$,
    INC_$IX_plus_D$,
    INC_$IY_plus_D$,
    DEC_Rp,
    DEC_$HL$,
    DEC_$IX_plus_D$,
    DEC_$IY_plus_D$,
    DAA,
    CPL,
    NEG,
    
    CCF,
    SCF,
    NOP,
    HALT,
    DI,
    EL,
    IM_0,
    IM_1,
    IM_2,

    ADD_HL_SS,
    ADC_HL_SS,
    SBC_HL_SS,
    ADD_IX_PP,
    ADD_IY_PP,
    INC_SS,
    INC_IX,
    INC_IY,
    DEC_SS,
    DEC_IX,
    DEC_IY,
    
    RLCA,
    RLA,
    RRCA,
    RRA,
    RLC_R,
    RLC_$HL$,
    RLC_$IX_plus_D$,
    RLC_$IY_plus_D$,
    RL_M,
    RRC_M,
    RR_M,
    SLA_M,
    SRA_M,
    SRL_M,
    RLD,
    RRD,
    BIT_B_R,
    BIT_B_$HL$,
    BIT_B_$IX_plus_D$,
    BIT_B_$IY_plus_D$,
    SET_B_R,
    SET_B_$HL$,
    SET_B_$IX_plus_D$,
    SET_B_$IY_plus_D$,
    RES_B_M,

    JP_NN,
    JP_CC_NN,
    JR_E,
    JR_C_E,
    JR_NC_E,
    JR_Z_E,
    JR_NZ_E,
    JP_$HL$,
    JP_$IX$,
    JP_$IY$,

    DJNZ_E,
    CALL_NN,
    CALL_CC_NN,
    RET,
    RET_CC,
    RETI,
    RETIN,
    RST_P,
    IN_A_$N$,
    IN_R_$C$,
    INI,
    INIR,
    IND,
    INDR,
    OUT_$N$_A,
    OUT_$C$_R,
    OUTI,
    OTIR,
    OUTD,
    OTDR,
};

enum Register{
    B,
    C,
    D,
    E,
    H,
    L,
    UNDEFINED,
    A
};

struct Instance{
    uint8_t MState;
    uint8_t TCycle;
    uint8_t instruction;
    uint8_t tmp;
    enum CpuState cpuState;

    enum Register registerIn;
    enum Register registerOut;

    uint16_t PC;
    uint16_t SP;
    uint16_t IX;
    uint16_t IY;
    uint8_t R;
    uint8_t I;
    
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;
    uint8_t H;
    uint8_t L;
    uint8_t Aprim;
    uint8_t Bprim;
    uint8_t Cprim;
    uint8_t Dprim;
    uint8_t Eprim;
    uint8_t Fprim;
    uint8_t Hprim;
    uint8_t Lprim;
};

#endif
