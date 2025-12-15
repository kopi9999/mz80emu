
#ifndef TESTDLL
#define TESTDLL

#include <stdio.h>
#include <stdlib.h>

#include "../moduleInternal.h"

struct Instance{
    uint8_t* data;
    uint32_t size;
    uint8_t readState;
    uint8_t writeState;
    uint8_t readTrigger;
};

#endif
