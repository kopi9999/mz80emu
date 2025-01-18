#include <stdbool.h>
#include <windows.h>
#include "loadlib.h"

void* loadlib(const char *restrict dllName)
{
    return LoadLibrary(TEXT(dllName));
}

void* loadfunc(void *restrict dll, const char *restrict funcName)
{
    return GetProcAddress((HINSTANCE) dll, "testdll");
}

bool unloadlib(void *restrict dll)
{
    return FreeLibrary((HINSTANCE) dll);
}
