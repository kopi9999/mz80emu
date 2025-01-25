#ifndef LOADLIB
#define LOADLIB
#include <stdint.h>

extern void* loadLib(const char*);
extern void* loadFunc(void*, const char*);
extern bool unloadLib(void*);
extern bool unloadLibs(void**, uint16_t);

#endif
