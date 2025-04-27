#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include "main.hpp"

extern void loadConfig();

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
