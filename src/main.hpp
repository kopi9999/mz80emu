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

struct InstanceInfo {
uint32_t instanceCount;
uint32_t* instancesList;
void** instancesParameters;
};

struct InterfacesInfo {
uint32_t interfacesCount;
uint32_t derivedInterfacesCount;
uint32_t totalInterfacesCount;
uint32_t* interfacesList;
uint16_t* interfacesLengths;
uint16_t* derivedInterfacesLengths;
DerivedInterfaceIds** derivedInterfacesList;
};

struct ClockInfo{
uint32_t clockPeriod;
uint32_t clockDepth;
uint32_t* strobeUpInstanceList;
uint32_t* strobeUpInterfacesList;
bool** strobeUpClock;
uint32_t* strobeDownInstanceList;
uint32_t* strobeDownInterfacesList;
bool** strobeDownClock;
};

#endif
