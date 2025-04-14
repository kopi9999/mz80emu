#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include "misc.hpp"

extern "C" {
    #include "loadlib.h"
    #include "misc.h"
    #include "modules\\moduleWindows.h"
}

using namespace std;

typedef enum Error (*createPtr)(void**, void*);
typedef enum Error (*createInterfacesPtr)(void*, void***, uint16_t*);
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

struct DerivedInterfaceIds {
    uint32_t interfacesId;
    uint32_t interfaceId;
};

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
    // loading from configuration file

    string loadingSteps[] = {
        "None",
        "Modules",
        "Module instances",
        "Interfaces",
        "Derived interfaces",
        "Clock period",
        "Clock depth",
        "Strobe up instances",
        "Strobe up interfaces",
        "Strobe up clock",
        "Strobe down instances",
        "Strobe down interfaces",
        "Strobe down clock"
    };
    uint32_t numberOfSteps = sizeof(loadingSteps) / sizeof(loadingSteps[0]);
    string currentLoadingStep = "None";
    bool loadingStepChange;
    string row;
    ifstream ConfigFile("../../config/config.txt");
    if (!ConfigFile) {
        cout << "ERROR: cannot find config.txt file\n";
        return 5;
    }

    vector<string> loadedModules;
    vector<string> loadedModuleInstances;
    vector<string> loadedInterfaces;
    vector<vector<vector<string>>> loadedDerivedInterfaces;
    string loadedClockPeriod;
    string loadedClockDepth;
    vector<string> loadedStrobeUpInstances;
    vector<string> loadedStrobeUpInterfaces;
    vector<vector<string>> loadedStrobeUpClock;
    vector<string> loadedStrobeDownInstances;
    vector<string> loadedStrobeDownInterfaces;
    vector<vector<string>> loadedStrobeDownClock;

    while (getline(ConfigFile, row)) {
        trim(&row);
        loadingStepChange = false;
        for (uint32_t i = 1; i < numberOfSteps; ++i) {
            if (row.rfind(loadingSteps[i], 0) == 0) {
                loadingStepChange = true;
                currentLoadingStep = loadingSteps[i];
                break;
            }
        }
        if (!loadingStepChange && !row.empty()) {
            if (currentLoadingStep == "Modules") {
                loadedModules.push_back(row);
            }
            else if (currentLoadingStep == "Module instances") {
                loadedModuleInstances.push_back(row);
            }
            else if (currentLoadingStep == "Interfaces") {
                loadedInterfaces.push_back(row);
            }
            else if (currentLoadingStep == "Derived interfaces") {
                
            }
            else if (currentLoadingStep == "Clock period") {
                loadedClockPeriod = row;
            }
            else if (currentLoadingStep == "Clock depth") {
                loadedClockDepth = row;
            }
            else if (currentLoadingStep == "Strobe up instances") {
                loadedStrobeUpInstances.push_back(row);
            }
            else if (currentLoadingStep == "Strobe up interfaces") {
                loadedStrobeUpInterfaces.push_back(row);
            }
            else if (currentLoadingStep == "Strobe up clock") {
                loadedStrobeUpClock.push_back(splitString(row, " "));
            }
            else if (currentLoadingStep == "Strobe down instances") {
                loadedStrobeDownInstances.push_back(row);
            }
            else if (currentLoadingStep == "Strobe down interfaces") {
                loadedStrobeDownInterfaces.push_back(row);
            }
            else if (currentLoadingStep == "Strobe down clock") {
                loadedStrobeDownClock.push_back(splitString(row, " "));
            }
        }
    }

    ConfigFile.close();

    // processing data loaded from configuration file

    modules.count = loadedModules.size(); //number of libraries to load
    modules.names = loadedModules;

    uint32_t instanceCount = loadedModuleInstances.size();
    uint32_t* instancesList = new uint32_t[instanceCount]; // id`s of libraries for instance creation
    void** instancesParameters = new void* [instanceCount]; // pointers to instance parameters (same id as instancesList)
    for (size_t i = 0; i < instanceCount; ++i) {
        instancesList[i] = stoul(loadedModuleInstances[i]);
        instancesParameters[i] = NULL;
    }

    uint32_t interfacesCount = loadedInterfaces.size();
    uint32_t derivedInterfacesCount = loadedDerivedInterfaces.size();
    uint32_t totalInterfacesCount = interfacesCount + derivedInterfacesCount;
    uint32_t* interfacesList = new uint32_t[totalInterfacesCount]; // id`s of instances for interfaces creation
    for (size_t i = 0; i < interfacesCount; ++i) {
        interfacesList[i] = stoul(loadedInterfaces[i]);
    }

    uint32_t** derivedInterfacesList = new uint32_t*[derivedInterfacesCount];
    for (size_t i = 0; i < derivedInterfacesCount; ++i) {
        uint32_t* derivedInterface = new uint32_t[2]; // Instead of 2 should be length of derived interface
        for (size_t j = 0; i < 2; ++i) {
            struct DerivedInterfaceIds derivedInterface = {0, 0}; // Loaded ids
            uint32_t derivedInterface[j] = derivedInterface;
        }
    }

    uint32_t clockPeriod = stoul(loadedClockPeriod); // time in nanoseconds
    uint32_t clockDepth = stoul(loadedClockDepth); // number of clock states

    uint32_t* strobeUpInstanceList = new uint32_t[instanceCount]; // strobe up order (instance id)
    uint32_t* strobeUpInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe up instance (interfaces id)
    bool** strobeUpClock = new bool* [instanceCount]; // strobe up activation for instances

    uint32_t* strobeDownInstanceList = new uint32_t[instanceCount]; // strobe down order (instance id)
    uint32_t* strobeDownInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe down instance (interfaces id)
    bool** strobeDownClock = new bool* [instanceCount]; // strobe down activation for instances

    for (size_t i = 0; i < instanceCount; ++i) {
        strobeUpInstanceList[i] = stoul(loadedStrobeUpInstances[i]);
        strobeUpInterfacesList[i] = stoul(loadedStrobeUpInterfaces[i]);
        strobeUpClock[i] = new bool[clockDepth];
        strobeDownInstanceList[i] = stoul(loadedStrobeDownInstances[i]);
        strobeDownInterfacesList[i] = stoul(loadedStrobeDownInterfaces[i]);
        strobeDownClock[i] = new bool[clockDepth];
        for (size_t j = 0; j < clockDepth; ++j) {
            strobeUpClock[i][j] = stringToBool(loadedStrobeUpClock[i][j]);
            strobeDownClock[i][j] = stringToBool(loadedStrobeDownClock[i][j]);
        }
    }

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
        error = modules.createInterfacesFuncs[tmpModuleId](&instances[interfacesList[i]], &interfaces[i], &interfacesElements[i]);
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
                error = modules.strobeUpFuncs[tmpModuleId](instances[strobeUpInstanceList[i]], (void**) &interfaces[strobeUpInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe up error " << error << ".\n"; break;}
            }
        }
        
        for (uint32_t i = 0; i < instanceCount; i++){
            if (strobeDownClock[i][clockState]){
                tmpModuleId = instancesList[strobeDownInstanceList[i]];
                error = modules.strobeDownFuncs[tmpModuleId](instances[strobeDownInstanceList[i]], (void**) &interfaces[strobeDownInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe down error " << error << ".\n"; break;}
            }
        }
        
        do {
        start = chrono::high_resolution_clock::now();
        } while (end > start);

        ++clockState;
        if (clockState == clockDepth) {clockState = 0;}

    }

    unloadLibs(modules.pointers, modules.count);
    return 0;
}

//test jocha
