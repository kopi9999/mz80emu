#include <stdbool.h>
#include <dlcfn.h>

#include "loadMod.h"

void* loadLib(const char *__restrict dllName)
{
    return dlopen(dllName, RTLD_NOW);
}

void* loadFunc(void *__restrict dll, const char *__restrict funcName)
{
    return dlsym(dll, funcName);
}

bool loadFuncs(void **__restrict funcTab, void ** __restrict dlls, uint16_t dllCount, const char *__restrict funcName)
{
    bool error = false;
    for (uint16_t i = 0; i < dllCount; i++){
        funcTab[i] = dlsym(dlls[i], funcName);
        if(!funcTab[i]){error = true;}
    }

    return error;
}

bool unloadLib(void *__restrict dll)
{
    return (bool) dlclose(dll);
}

bool unloadLibs(void **__restrict dlls, uint16_t dllCount)
{
    bool error = false;
    bool errortmp;
    for (uint16_t i = 0; i < dllCount; i++)
    {
        if (!dlls[i]){continue;}
        errortmp = dlclose(dlls[i]);
        if (errortmp) {error = true;}
    }
    return error;
}
