#ifndef TESTDLL
#define TESTDLL

#include <stdio.h>
#include <stdlib.h>

#include "../moduleInternal.h"

struct Instance{
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
