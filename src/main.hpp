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
extern void** instances;
extern void*** interfaces;
extern uint16_t* interfacesElements;

extern uint32_t instanceCount;
extern uint32_t* instancesList;
extern void** instancesParameters;

extern uint32_t interfacesCount;
extern uint32_t derivedInterfacesCount;
extern uint32_t totalInterfacesCount;
extern uint32_t* interfacesList;
extern DerivedInterfaceIds** derivedInterfacesList;
extern uint32_t* derivedInterfacesLengths;

extern uint32_t clockPeriod;
extern uint32_t clockDepth;

extern uint32_t* strobeUpInstanceList;
extern uint32_t* strobeUpInterfacesList;
extern bool** strobeUpClock;
extern uint32_t* strobeDownInstanceList;
extern uint32_t* strobeDownInterfacesList;
extern bool** strobeDownClock;

#endif
