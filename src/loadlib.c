#include <stdbool.h>
#include <windows.h>

#include "loadlib.h"

void* loadLib(const char *__restrict dllName)
{
    return LoadLibrary(TEXT(dllName));
}

void* loadFunc(void *__restrict dll, const char *funcName)
{
    return GetProcAddress((HINSTANCE) dll, funcName);
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
