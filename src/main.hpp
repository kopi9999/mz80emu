#ifndef MAIN
#define MAIN

#include <vector>
#include <string>
extern "C" {
    #include "modules\\moduleWindows.h"
}

typedef enum Error (*createPtr)(void**, void*);
typedef enum Error (*createInterfacesPtr)(void*, void***, uint16_t*);
typedef enum Error (*strobeUpPtr)(void*, void**);
typedef enum Error (*strobeDownPtr)(void*, void**);
typedef enum Error (*destroyPtr)(void*);
typedef enum Error (*destroyInterfacesPtr)(void*, void**, uint16_t);

struct Modules {
    std::vector<std::string> names;
    uint16_t count;
    void** pointers;
    createPtr* createFuncs;
    createInterfacesPtr* createInterfacesFuncs;
    strobeUpPtr* strobeUpFuncs;
    strobeDownPtr* strobeDownFuncs;
    destroyPtr* destroyFuncs;
    destroyInterfacesPtr* destroyInterfacesFuncs;
};

struct DerivedInterfaceIds {
    uint32_t interfacesId;
    uint32_t interfaceId;
};

extern struct Modules modules;

#endif
