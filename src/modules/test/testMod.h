
#ifndef TESTDLL
#define TESTDLL

#include <stdio.h>
#include <stdlib.h>

#include "../moduleInternal.h"

struct Instance{
    uint8_t value;
    char* character;
};

extern void destroyGarbageCollect(struct Instance* instance);
extern void destroyInterfacesGarbageCollect(void** interfaces);

#endif
