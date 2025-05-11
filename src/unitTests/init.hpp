#ifndef TEST_INIT_FUNCTIONS
#define TEST_INIT_FUNCTIONS

#include "../main.hpp"

extern bool loadLibs(void** libs, std::vector<std::string> libNames, uint16_t libCount);
extern bool loadModuleFunctions(struct Modules modules);
extern bool loadInstances(struct Modules modules, void** instances, struct InstanceInfo instanceInfo);
extern bool loadInterfaces(struct Modules modules, void** instances, void*** interfaces, const uint32_t* instancesList, struct InterfacesInfo interfacesInfo);
extern bool loadDerivedInterfaces(void*** interfaces, struct InterfacesInfo interfacesInfo);

#endif
