#include <stdio.h>
#include <windows.h>

extern "C" {
	#include "test.h"
    #include "loadlib.h"
}

int main()
{
	printf("\nPlaceholder: %d\n\n", test());
    void* lib = loadlib("test.dll");
    printf("library pointer: %x\n", lib);
    if (!lib) {printf("error, cant find lib"); return 1;}
    int (*func) () = (int (*)()) loadfunc(lib, "testdll");
    printf("function pointer: %x\n", func);
    if (!func) {printf("error, cant find func"); return 2;}
    printf("dll test: %d\n", func());
    unloadlib(lib);
}

//test jocha
