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

enum CrashCode{
    RUNNING,
    CONFIG_NOT_FOUND,
    CONFIG_VALUE_NAN,
    CONFIG_VALUE_NOT_BOOL,
    CONFIG_VALUE_INVALID,
    CONFIG_DERIVED_INTERFACE_INVALID,
    CONFIG_TOO_MANY_VALUES,
    CONFIG_INVALID_NUMBER_OF_VALUES,
    CONFIG_ID_DOES_NOT_EXIST,
    CONFIG_INSTANCE_NUMBER_INCONSISTENT,
    
    INIT_MODULE_NOT_FOUND,
    INIT_MODULE_INVALID,
    INIT_INSTANCE_CREATION_ERROR,
    INIT_INTERFACES_CREATION_ERROR,
    INIT_DERIVED_INTERFACES_CREATION_ERROR,

};

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
uint32_t count;
uint32_t* list;
void** parameters;
};

struct InterfacesInfo {
uint32_t count;
uint32_t derivedCount;
uint32_t totalCount;
uint32_t* list;
DerivedInterfaceIds** derivedList;
uint16_t* lengths;
uint16_t* derivedLengths;
};

struct ClockInfo{
uint32_t period;
uint32_t depth;
uint32_t* strobeUpInstanceList;
uint32_t* strobeUpInterfacesList;
bool** strobeUpClock;
uint32_t* strobeDownInstanceList;
uint32_t* strobeDownInterfacesList;
bool** strobeDownClock;
};

#endif
