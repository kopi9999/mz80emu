#include <stdbool.h>
#include <windows.h>

#include "loadlib.h"

void* loadLib(const char *__restrict dllName)
{
    return LoadLibrary(TEXT(dllName));
}

void* loadFunc(void *__restrict dll, const char *__restrict funcName)
{
    return GetProcAddress((HINSTANCE) dll, funcName);
}

bool loadFuncs(void **__restrict funcTab, void ** __restrict dlls, uint16_t dllCount, const char *__restrict funcName)
{
    bool error = false;
    for (uint16_t i = 0; i < dllCount; i++){
        funcTab[i] = GetProcAddress((HINSTANCE) dlls[i], funcName);
        if(!funcTab[i]){error = true;}
    }

    return error;
}

bool unloadLib(void *__restrict dll)
{
    return FreeLibrary((HINSTANCE) dll);
}

bool unloadLibs(void **__restrict dlls, uint16_t dllCount)
{
    bool error = false;
    bool errortmp;
    for (uint16_t i = 0; i < dllCount; i++)
    {
        if (!dlls[i]){continue;}
        errortmp = FreeLibrary((HINSTANCE) dlls);
        if (errortmp) {error = true;}
    }
    return error;
}
