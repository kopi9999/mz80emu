#ifndef LOADLIB
#define LOADLIB

extern void* loadlib(const char*);
extern void* loadfunc(void*, const char*);
extern bool unloadlib(void*);

#endif
