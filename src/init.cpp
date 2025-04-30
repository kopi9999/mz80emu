#include "init.hpp"
#include "main.hpp"
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

bool loadModuleFunctions()
{
    modules.createFuncs = new createPtr[modules.count];
    modules.createInterfacesFuncs = new createInterfacesPtr[modules.count];
    modules.strobeUpFuncs = new strobeUpPtr[modules.count];
    modules.strobeDownFuncs = new strobeDownPtr[modules.count];
    modules.destroyFuncs = new destroyPtr[modules.count];
    modules.destroyInterfacesFuncs = new destroyInterfacesPtr[modules.count];

    if (loadFuncs((void**) modules.createFuncs, modules.pointers, modules.count, "create")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.createFuncs, modules.count)] << "]: Cannot load all functions.\n";
        return false;
    }
    if (loadFuncs((void**) modules.createInterfacesFuncs, modules.pointers, modules.count, "createInterfaces")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.createInterfacesFuncs, modules.count)] << "]: Cannot load all functions.\n";
        return false;
    }
    if (loadFuncs((void**) modules.strobeUpFuncs, modules.pointers, modules.count, "strobeUp")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.strobeUpFuncs, modules.count)] << "]: Cannot load all functions.\n";
        return false;
    }
    if (loadFuncs((void**) modules.strobeDownFuncs, modules.pointers, modules.count, "strobeDown")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.strobeDownFuncs, modules.count)] << "]: Cannot load all functions.\n";
        return false;
    }
    if (loadFuncs((void**) modules.destroyFuncs, modules.pointers, modules.count, "destroy")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.destroyFuncs, modules.count)] << "]: Cannot load all functions.\n";
        return false;
    }
    if (loadFuncs((void**) modules.destroyInterfacesFuncs, modules.pointers, modules.count, "destroyInterfaces")){
        cout << "ERROR [" << modules.names[firstNullPointer((void**) modules.destroyInterfacesFuncs, modules.count)] << "]: Cannot load all functions.\n";
        return false;
    }

    cout << "INFO: All modules succesfully loaded\n";
    return true;
}

int init()
{

    modules.pointers = new void*[modules.count];
    
    if (loadLibs(modules.pointers, modules.names, modules.count))
    {
        unloadLibs(modules.pointers, modules.count);
        return 1;

    }
   
    if (!loadModuleFunctions()){
        unloadLibs(modules.pointers, modules.count);
        return 2;
    }

    //creating instances and interfaces
    
    instances = new void*[instanceCount];
    Error error;

    for (uint32_t i = 0; i < instanceCount; i++){
        error = modules.createFuncs[instancesList[i]](&instances[i], instancesParameters[i]);
        if (error) { cout << "ERROR [" << modules.names[instancesList[i]] << "]: Cannot create instance " << i << " , error " << error << ".\n"; break; }
    }
    if (error) { unloadLibs(modules.pointers, modules.count); return 3; }

    cout << "INFO: All instances created successfully\n";

    interfaces = new void**[totalInterfacesCount];
    interfacesElements = new uint16_t[interfacesCount];
    uint16_t tmpModuleId;
    
    for (uint32_t i = 0; i < interfacesCount; i++){
        tmpModuleId = instancesList[interfacesList[i]];
        error = modules.createInterfacesFuncs[tmpModuleId](&instances[interfacesList[i]], &interfaces[i], &interfacesElements[i]);
        if (error) { cout << "ERROR [" << modules.names[tmpModuleId] << "]: Cannot create interfaces " << i << " , error " << error << ".\n"; break; }
    }
    if (error) { unloadLibs(modules.pointers, modules.count); return 4; }

    for (uint32_t i = 0; i < derivedInterfacesCount; i++){
       interfaces[i + interfacesCount] = new void*[derivedInterfacesLengths[i]];
       for (uint32_t j = 0; j < derivedInterfacesLengths[i]; j++){
            //if (!validateIdExist(derivedInterfacesList[i][j].interfaceId, interfacesElements[derivedInterfacesList[i][j].interfacesId] - 1, "Derived interfaces")) {return 11;}
            interfaces[i + interfacesCount][j] = interfaces[derivedInterfacesList[i][j].interfacesId][derivedInterfacesList[i][j].interfaceId];
       }
    }

    cout << "INFO: All interfaces created successfully\n";
    return 0;
}
