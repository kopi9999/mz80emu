#include "init.hpp"
#include "validation.hpp"
#include <iostream>
extern "C" {
    #include "loadMod.h"
    #include "misc.h"
}

using namespace std;

bool loadLibs(void** libs, vector<string> libNames, uint16_t libCount) //load libraries from std::vector<string>
{
    bool error = false;
    for (uint16_t i = 0; i < libCount; ++i)
    {
        libs[i] = loadLib(("modules/" + libNames[i]).c_str());
        if(!libs[i]){
            cout << "ERROR: module loading failed: " << getError() << "\n";
            error = true;
        }
        else 
        {
            cout << "INFO: Loading module: " << libNames[i] << "\n";
        }
    }
    return error;
}

bool loadModuleFunctions(struct Modules modules)
{
    if (loadFuncs((void**) modules.createFuncs, modules.pointers, modules.count, "create")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.createFuncs, modules.count)] << "]: " << getError() << "\n";
        return false;
    }
    if (loadFuncs((void**) modules.createInterfacesFuncs, modules.pointers, modules.count, "createInterfaces")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.createInterfacesFuncs, modules.count)] << "]: " << getError() << "\n";
        return false;
    }
    if (loadFuncs((void**) modules.strobeUpFuncs, modules.pointers, modules.count, "strobeUp")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.strobeUpFuncs, modules.count)] << "]: " << getError() << "\n";
        return false;
    }
    if (loadFuncs((void**) modules.strobeDownFuncs, modules.pointers, modules.count, "strobeDown")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.strobeDownFuncs, modules.count)] << "]: " << getError() << "\n";
        return false;
    }
    if (loadFuncs((void**) modules.destroyFuncs, modules.pointers, modules.count, "destroy")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.destroyFuncs, modules.count)] << "]: " << getError() << "\n";
        return false;
    }
    if (loadFuncs((void**) modules.destroyInterfacesFuncs, modules.pointers, modules.count, "destroyInterfaces")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.destroyInterfacesFuncs, modules.count)] << "]: " << getError() << "\n";
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

bool loadUiLibs(void** libs, vector<string> libNames, uint16_t libCount) //load libraries from std::vector<string>
{
    bool error = false;
    for (uint16_t i = 0; i < libCount; ++i)
    {
        libs[i] = loadLib(("uiModules/" + libNames[i]).c_str());
        if(!libs[i]){
            cout << "ERROR: loading UI module failed: " << getError() << "\n";
            error = true;
        }
        else 
        {
            cout << "INFO: Loading UI module: " << libNames[i] << "\n";
        }
    }
    return error;
}

bool loadUiModuleFunctions(struct UiModules uiModules)
{
    if (loadFuncs((void**) uiModules.getFrameFuncs, uiModules.pointers, uiModules.count, "_Z8getFramePvPS_")){
        cout << "ERROR [" << uiModules.names[firstNullPointer((void**) uiModules.getFrameFuncs, uiModules.count)] << "]: " << getError() << "\n";
        return false;
    }
    return true;
}

bool loadUiInstances(struct UiModules uiModules, wxFrame** uiInstances, void** instances, void*** interfaces, struct UiInstanceInfo uiInstanceInfo)
{
    for (uint32_t i = 0; i < uiInstanceInfo.count; i++){
        uiInstances[i] = uiModules.getFrameFuncs[uiInstanceInfo.uiInstanceList[i]](instances[uiInstanceInfo.instanceList[i]], interfaces[uiInstanceInfo.interfaceArrayList[i]]);
    }
    return true;
}

enum CrashCode init(
    struct Modules* modules,
    struct UiModules* uiModules,
    void*** instances,
    wxFrame*** uiInstances,
    void**** interfaces,
    struct InstanceInfo instanceInfo,
    struct UiInstanceInfo uiInstanceInfo,
    struct InterfacesInfo interfacesInfo
)
{
    modules->pointers = new void*[modules->count];
    uiModules->pointers = new void*[uiModules->count];
    if(loadLibs(modules->pointers, modules->names, modules->count)){
        cout << "CRITICAL: Could not load all modules\n";
        unloadLibs(modules->pointers, modules->count);
        return INIT_MODULE_NOT_FOUND;
    }
    if(loadUiLibs(uiModules->pointers, uiModules->names, uiModules->count)){
        cout << "CRITICAL: Could not load all UI modules\n";
        unloadLibs(modules->pointers, modules->count);
        unloadLibs(uiModules->pointers, uiModules->count);
        return INIT_MODULE_NOT_FOUND;
    }

    modules->createFuncs = new createPtr[modules->count];
    modules->createInterfacesFuncs = new createInterfacesPtr[modules->count];
    modules->strobeUpFuncs = new strobeUpPtr[modules->count];
    modules->strobeDownFuncs = new strobeDownPtr[modules->count];
    modules->destroyFuncs = new destroyPtr[modules->count];
    modules->destroyInterfacesFuncs = new destroyInterfacesPtr[modules->count];
    if (!loadModuleFunctions(*modules)){
        cout << "CRITICAL: Could not load all modules properly\n";
        unloadLibs(modules->pointers, modules->count);
        unloadLibs(uiModules->pointers, uiModules->count);
        return INIT_MODULE_INVALID;
    }
    cout << "INFO: All modules succesfully loaded\n";
    
    uiModules->getFrameFuncs = new getFrame[uiModules->count];
    if (!loadUiModuleFunctions(*uiModules)){
        cout << "CRITICAL: Could not load all UI modules properly\n";
        unloadLibs(modules->pointers, modules->count);
        unloadLibs(uiModules->pointers, uiModules->count);
        return INIT_MODULE_INVALID;
    }
    cout << "INFO: All UI modules successfully loaded\n";

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

    *uiInstances = new wxFrame*[uiInstanceInfo.count];
    if (!loadUiInstances(*uiModules, *uiInstances, *instances, *interfaces, uiInstanceInfo)){
        cout << "CRITICAL: Could not create needed UI instances\n";
        return INIT_INSTANCE_CREATION_ERROR;
    }
    cout << "INFO: All UI instances created successfully\n";

    return RUNNING;
}
