#ifndef MODULE_INTERNAL
#define MODULE_INTERNAL

#ifdef _WIN32
    #include "moduleWindows.h"
#else
    #include "module.h"
#endif

extern const char* moduleName;
extern const char* moduleDescription;

#endif
