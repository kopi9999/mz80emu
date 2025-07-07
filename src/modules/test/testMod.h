
#ifndef TESTDLL
#define TESTDLL

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include "../moduleWindows.h"
#else
    #include "../module.h"
#endif 

struct Instance{
    uint8_t value;
    char* character;
};

extern void destroyGarbageCollect(struct Instance* instance);
extern void destroyInterfacesGarbageCollect(void** interfaces);

#endif
