#include <stdbool.h>
#include <windows.h>
#include "loadlib.h"

void* loadlib(const char *__restrict dllName)
{
    return LoadLibrary(TEXT(dllName));
}

void* loadfunc(void *__restrict dll, const char *funcName)
{
    return GetProcAddress((HINSTANCE) dll, "testdll");
}

bool unloadlib(void *__restrict dll)
{
    return FreeLibrary((HINSTANCE) dll);
}
