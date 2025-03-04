#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <chrono>

extern "C" {
    #include "loadlib.h"
    #include "misc.h"
    #include "modules\\moduleWindows.h"
}

using namespace std;

typedef enum Error (*createPtr)(void*, void*);
typedef enum Error (*createInterfacesPtr)(void*, void**, uint16_t*);
typedef enum Error (*strobeUpPtr)(void*, void**);
typedef enum Error (*strobeDownPtr)(void*, void**);
typedef enum Error (*destroyPtr)(void*);
typedef enum Error (*destroyInterfacesPtr)(void*, void**, uint16_t);

struct Modules {
    vector<string> names;
    uint16_t count;
    void** pointers;
    createPtr* createFuncs;
    createInterfacesPtr* createInterfacesFuncs;
    strobeUpPtr* strobeUpFuncs;
    strobeDownPtr* strobeDownFuncs;
    destroyPtr* destroyFuncs;
    destroyInterfacesPtr* destroyInterfacesFuncs;
} modules;

void** instances;
void*** interfaces;
uint16_t* interfacesElements;


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

int main()
{
    // loading from config file

    modules.names.push_back("test.dll");
    modules.count = modules.names.size(); //number of libraries to load

    uint32_t instanceCount = 2; // number of instances
    uint32_t* instancesList = new uint32_t[instanceCount]{0, 0}; // id`s of libraries for instance creation
    void** instancesParameters = new void*[instanceCount]{NULL, NULL}; // pointers to instance parameters (same id as instancesList)

    uint32_t interfacesCount = 1; // number of interfaces
    uint32_t* interfacesList = new uint32_t[interfacesCount]{0}; // id`s of instances for interfaces creation

    uint32_t clockPeriod = 500000000; // 0.5s in nanoseconds
    uint32_t clockDepth = 2; // number of clock states
    
    uint32_t* strobeUpInstanceList = new uint32_t[instanceCount]{0, 1}; // strobe up order (instance id)
    uint32_t* strobeUpInterfacesList = new uint32_t[instanceCount]{0, 0}; // interfaces given for every strobe up instance (interfaces id)
    bool** strobeUpClock = new bool*[instanceCount]{
        new bool[clockDepth]{true, false}, // strobe up activation for first instance
        new bool[clockDepth]{false, true}  // strobe up activation for second instance (180 deg. phase shift)
    };

    uint32_t* strobeDownInstanceList = new uint32_t[instanceCount]{0, 1}; // strobe down order (instance id)
    uint32_t* strobeDownInterfacesList = new uint32_t[instanceCount]{0, 0}; // interfaces given for every strobe down instance (interfaces id)
    bool** strobeDownClock = new bool*[instanceCount]{
        new bool[clockDepth]{false, true}, // strobe down activation for first instance
        new bool[clockDepth]{true, false}  // strobe down activation for second instance (180 deg. phase shift)
    };

    // end of config file
    // loading modules
    
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

    interfaces = new void**[interfacesCount];
    interfacesElements = new uint16_t[interfacesCount];
    uint16_t tmpModuleId;
    
    for (uint32_t i = 0; i < interfacesCount; i++){
        tmpModuleId = instancesList[interfacesList[i]];
        error = modules.createInterfacesFuncs[tmpModuleId](&instances[interfacesList[i]], (void**) &interfaces[i], &interfacesElements[i]);
        if (error) { cout << "ERROR [" << modules.names[tmpModuleId] << "]: Cannot create interfaces " << i << " , error " << error << ".\n"; break; }
    }
    if (error) { unloadLibs(modules.pointers, modules.count); return 4; }

    cout << "INFO: All interfaces created successfully\n";

    //main loop

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::nanoseconds duration = chrono::nanoseconds(clockPeriod);
    uint32_t clockState = 0;

    while (true){
        start = chrono::high_resolution_clock::now();
        end = start + duration;

        for (uint32_t i = 0; i < instanceCount; i++){
            if (strobeUpClock[i][clockState]){
                tmpModuleId = instancesList[strobeUpInstanceList[i]];
                error = modules.strobeUpFuncs[tmpModuleId](&instances[strobeUpInstanceList[i]], (void**) &interfaces[strobeUpInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe up error " << error << ".\n"; break;}
            }
        }
        
        for (uint32_t i = 0; i < instanceCount; i++){
            if (strobeDownClock[i][clockState]){
                tmpModuleId = instancesList[strobeDownInstanceList[i]];
                error = modules.strobeDownFuncs[tmpModuleId](&instances[strobeDownInstanceList[i]], (void**) &interfaces[strobeDownInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe down error " << error << ".\n"; break;}
            }
        }
        
        do {
        start = chrono::high_resolution_clock::now();
        } while (end > start);

    }

    unloadLibs(modules.pointers, modules.count);
    return 0;
}

//test jocha
