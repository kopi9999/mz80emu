#include "init.hpp"
#include "validation.hpp"
#include <iostream>
extern "C" {
    #include "loadlib.h"
    #include "misc.h"
}

using namespace std;

bool loadLibs(void** libs, vector<string> libNames, uint16_t libCount) //load libraries from std::vector<string>
{
    bool error = false;
    for (uint16_t i = 0; i < libCount; ++i)
    {
        libs[i] = loadLib(libNames[i].c_str());
        if(!libs[i]){
            cout << "ERROR: cannot find module: " << libNames[i] << "\n";
            error = true;
        }
        else 
        {
            cout << "INFO: Loading module: " << libNames[i] << "\n";
        }
    }
    return error;
}

bool loadModuleFunctions(struct Modules* modules)
{
    modules->createFuncs = new createPtr[modules->count];
    modules->createInterfacesFuncs = new createInterfacesPtr[modules->count];
    modules->strobeUpFuncs = new strobeUpPtr[modules->count];
    modules->strobeDownFuncs = new strobeDownPtr[modules->count];
    modules->destroyFuncs = new destroyPtr[modules->count];
    modules->destroyInterfacesFuncs = new destroyInterfacesPtr[modules->count];

    if (loadFuncs((void**) modules->createFuncs, modules->pointers, modules->count, "create")){
        cout << "ERROR [" << modules->names[firstNullPointer((void**) modules->createFuncs, modules->count)] << "]: Cannot load create function.\n";
        return false;
    }
    if (loadFuncs((void**) modules->createInterfacesFuncs, modules->pointers, modules->count, "createInterfaces")){
        cout << "ERROR [" << modules->names[firstNullPointer((void**) modules->createInterfacesFuncs, modules->count)] << "]: Cannot load createInterfaces function.\n";
        return false;
    }
    if (loadFuncs((void**) modules->strobeUpFuncs, modules->pointers, modules->count, "strobeUp")){
        cout << "ERROR [" << modules->names[firstNullPointer((void**) modules->strobeUpFuncs, modules->count)] << "]: Cannot load strobeUp function.\n";
        return false;
    }
    if (loadFuncs((void**) modules->strobeDownFuncs, modules->pointers, modules->count, "strobeDown")){
        cout << "ERROR [" << modules->names[firstNullPointer((void**) modules->strobeDownFuncs, modules->count)] << "]: Cannot load strobeDown function.\n";
        return false;
    }
    if (loadFuncs((void**) modules->destroyFuncs, modules->pointers, modules->count, "destroy")){
        cout << "ERROR [" << modules->names[firstNullPointer((void**) modules->destroyFuncs, modules->count)] << "]: Cannot load destroy function.\n";
        return false;
    }
    if (loadFuncs((void**) modules->destroyInterfacesFuncs, modules->pointers, modules->count, "destroyInterfaces")){
        cout << "ERROR [" << modules->names[firstNullPointer((void**) modules->destroyInterfacesFuncs, modules->count)] << "]: Cannot load destroyInterfaces function.\n";
        return false;
    }

    return true;
}

bool loadModules(struct Modules* modules)
{
    if (loadLibs(modules->pointers, modules->names, modules->count))
    {
        unloadLibs(modules->pointers, modules->count);
        return false;

    }
  return true;
}
bool loadModuleFunctions(struct Modules modules)
{
    if (!loadModuleFunctions(modules)){
        unloadLibs(modules.pointers, modules.count);
        return false;
    }
    return true;
}


bool loadInstances(struct Modules modules, void** instances, struct InstanceInfo instanceInfo)
{
    Error error;

    for (uint32_t i = 0; i < instanceInfo.count; i++){
        error = modules.createFuncs[instanceInfo.list[i]](&instances[i], instanceInfo.parameters[i]);
        if (error) { cout << "ERROR [" << modules.names[instanceInfo.list[i]] << "]: Cannot create instance " << i << " , error " << error << ".\n"; break; }
    }
    if (error) { unloadLibs(modules.pointers, modules.count); return false; }
    return true;
}

bool loadInterfaces(struct Modules modules, void** instances, void*** interfaces, const uint32_t* instancesList, struct InterfacesInfo interfacesInfo)
{
    Error error;
    uint16_t tmpModuleId;
    
    for (uint32_t i = 0; i < interfacesInfo.count; i++){
        tmpModuleId = instancesList[interfacesInfo.list[i]];
        error = modules.createInterfacesFuncs[tmpModuleId](&instances[interfacesInfo.list[i]], &interfaces[i], &interfacesInfo.lengths[i]);
        if (error) { cout << "ERROR [" << modules.names[tmpModuleId] << "]: Cannot create interfaces " << i << " , error " << error << ".\n"; break; }
    }
    if (error) { unloadLibs(modules.pointers, modules.count); return false; }
    return true;
}

bool loadDerivedInterfaces(void*** interfaces, struct InterfacesInfo interfacesInfo)
{
    for (uint32_t i = 0; i < interfacesInfo.derivedCount; i++){
       interfaces[i + interfacesInfo.count] = new void*[interfacesInfo.derivedLengths[i]];
       for (uint32_t j = 0; j < interfacesInfo.derivedLengths[i]; j++){
            if (!validateIdExist(interfacesInfo.derivedList[i][j].interfaceId, interfacesInfo.lengths[interfacesInfo.derivedList[i][j].interfacesId] - 1, "Derived interfaces")) {return false;}
            interfaces[i + interfacesInfo.count][j] = interfaces[interfacesInfo.derivedList[i][j].interfacesId][interfacesInfo.derivedList[i][j].interfaceId];
       }
    }

    return true;
}

enum CrashCode init(struct Modules* modules, void*** instances, void**** interfaces, struct InstanceInfo instanceInfo, struct InterfacesInfo interfacesInfo)
{
    uint8_t error;
    modules->pointers = new void*[modules->count];
    error = loadModules(modules);
    if(!loadModules(modules)){
        cout << "CRITICAL: Could not find all modules\n";
        return INIT_MODULE_NOT_FOUND;
    } 
    if (!loadModuleFunctions(*modules)){
        cout << "CRITICAL: Could not load all modules properly\n";
        return INIT_MODULE_INVALID;
    }
    cout << "INFO: All modules succesfully loaded\n";

    *instances = new void*[instanceInfo.count];
    if (!loadInstances(*modules, *instances, instanceInfo)){
        cout << "CRITICAL: Could not create needed instances\n";
        return INIT_INSTANCE_CREATION_ERROR;
    }
    cout << "INFO: All instances created successfully\n";

    *interfaces = new void**[interfacesInfo.totalCount];
    if (!loadInterfaces(*modules, *instances, *interfaces, instanceInfo.list, interfacesInfo)){
        cout << "CRITICAL: Could not create needed interfaces\n";
        return INIT_INTERFACES_CREATION_ERROR;
    }
    cout << "INFO: All interfaces created successfully\n";

    if(!loadDerivedInterfaces(*interfaces, interfacesInfo)){
        cout << "CRITICAL: Could not create needed derived interfaces";
        return INIT_DERIVED_INTERFACES_CREATION_ERROR;
    }
    cout << "INFO: All derived interfaces created successfully.\n";

    return RUNNING;
}
