#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "loadConfig.hpp"
#include "validation.hpp"
#include "main.hpp"
#include "misc.hpp"

using namespace std;

enum LoadingSteps {
    NONE,
    MODULES,
    MODULE_INSTANCES,
    INTERFACES,
    DERIVED_INTERFACES,
    CLOCK_PERIOD,
    CLOCK_DEPTH,
    STROBE_UP_INSTANCES,
    STROBE_UP_INTERFACES,
    STROBE_UP_CLOCK,
    STROBE_DOWN_INSTANCES,
    STROBE_DOWN_INTERFACES,
    STROBE_DOWN_CLOCK,

    NUMBER_OF_STEPS
};

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


enum LoadingSteps detectLoadingStep(string row)
{
    const string loadingSteps[] = {
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
    for (uint32_t i = 1; i < NUMBER_OF_STEPS; ++i) {
       if (row.rfind(loadingSteps[i], 0) == 0){
            return (enum LoadingSteps) i;
       } 
    }
    return NONE;
}

int loadLineData(string row, enum LoadingSteps currentLoadingStep)
{
    vector<string> splittedRow;
    switch (currentLoadingStep){
        case MODULES:
            loadedModules.push_back(row);
            break;
        case MODULE_INSTANCES:
            if (!validateStringIsInteger(row, "Module instances")) {return 6;}
            loadedModuleInstances.push_back(row);
            break;
        case INTERFACES:
            if (!validateStringIsInteger(row, "Interfaces")) {return 6;}
            loadedInterfaces.push_back(row);
            break;
        case DERIVED_INTERFACES:
            if (row == "new") {
                loadedDerivedInterfaces.push_back({});
            } else {
                if (!validateDerivedInterfaceCreated(loadedDerivedInterfaces)) {return 9;}
                splittedRow = splitByWhitespace(row);
                if (!validateVectorSize(splittedRow, 2, "Derived interfaces")) {return 8;}
                if (!validateStringIsInteger(splittedRow[0], "Derived interfaces") || !validateStringIsInteger(splittedRow[1], "Derived interfaces")) {return 6;}
                loadedDerivedInterfaces[loadedDerivedInterfaces.size() - 1].push_back(splittedRow);
            }
            break;
        case CLOCK_PERIOD:
            if (!validateStringIsInteger(row, "Clock period")) {return 6;}
            loadedClockPeriod = row;
            break;
        case CLOCK_DEPTH:
            if (!validateStringIsInteger(row, "Clock depth")) {return 6;}
            loadedClockDepth = row;
            break;
        case STROBE_UP_INSTANCES:
            if (!validateStringIsInteger(row, "Strobe up instances")) {return 6;}
            loadedStrobeUpInstances.push_back(row);
            break;
        case STROBE_UP_INTERFACES:
            if (!validateStringIsInteger(row, "Strobe up interfaces")) {return 6;}
            loadedStrobeUpInterfaces.push_back(row);
            break;
        case STROBE_UP_CLOCK:
            splittedRow = splitByWhitespace(row);
            for (int i=0; i<splittedRow.size(); i++) {
                if (!validateStringIsBool(splittedRow[i], "Strobe up clock")) {return 7;}
            }
            loadedStrobeUpClock.push_back(splittedRow);
            break;
        case STROBE_DOWN_INSTANCES:
            if (!validateStringIsInteger(row, "Strobe down clock")) {return 6;}
            loadedStrobeDownInstances.push_back(row);
            break;
        case STROBE_DOWN_INTERFACES:
            if (!validateStringIsInteger(row, "Strobe down interfaces")) {return 6;}
            loadedStrobeDownInterfaces.push_back(row);
            break;
        case STROBE_DOWN_CLOCK:
            splittedRow = splitByWhitespace(row);
            for (int i=0; i<splittedRow.size(); i++) {
                if (!validateStringIsBool(splittedRow[i], "Strobe down clock")) {return 7;}
            }
            loadedStrobeDownClock.push_back(splittedRow);
            break;

        case NONE:
            return 0;
        case NUMBER_OF_STEPS:
            return 0;
    }
    return 0;
}

int loadDataFromFile() 
{
    enum LoadingSteps currentLoadingStep = NONE;
    enum LoadingSteps loadingStep = NONE;
    bool loadingStepChange;
    string row;
    ifstream ConfigFile("../../config/config.txt");
    if (!ConfigFile) {
        cout << "ERROR: cannot find config.txt file\n";
        return 5;
    }

    while (getline(ConfigFile, row)) {
        trim(&row);
        loadingStepChange = false;
        loadingStep = detectLoadingStep(row);
        if (loadingStep) {
            loadingStepChange = true;
            currentLoadingStep = loadingStep;
        }
        if (!loadingStepChange && !row.empty()) {
            loadLineData(row, currentLoadingStep);
        }
    }

    ConfigFile.close();
    return 0;
}

int setInstanceData(struct Modules* modules, struct InstanceInfo* instanceInfo)
{
    modules->count = loadedModules.size(); //number of libraries to load
    modules->names = loadedModules;

    instanceInfo->count = loadedModuleInstances.size();
    instanceInfo->list = new uint32_t[instanceInfo->count]; // id`s of libraries for instance creation
    instanceInfo->parameters = new void* [instanceInfo->count]; // pointers to instance parameters (same id as instancesList)
    for (size_t i = 0; i < instanceInfo->count; ++i) {
        if (!validateIdExist(stoul(loadedModuleInstances[i]), modules->count - 1, "Module instances")) {return 11;}
        instanceInfo->list[i] = stoul(loadedModuleInstances[i]);
        instanceInfo->parameters[i] = NULL;
    }
    return 0;
}

int setInterfacesData(struct InterfacesInfo* data, uint32_t instanceCount)
{
    data->count = loadedInterfaces.size();
    data->derivedCount = loadedDerivedInterfaces.size();
    data->totalCount = data->count + data->derivedCount;
    data->list = new uint32_t[data->totalCount]; // id`s of instances for interfaces creation
    data->lengths = new uint16_t[data->count];
    for (size_t i = 0; i < data->count; ++i) {
        if (!validateIdExist(stoul(loadedInterfaces[i]), instanceCount - 1, "Interfaces")) {return 11;}
        data->list[i] = stoul(loadedInterfaces[i]);
    }

    data->derivedList = new DerivedInterfaceIds*[data->derivedCount];
    data->derivedLengths = new uint16_t[data->derivedCount]; // lengths of all derived interfaces tables
    DerivedInterfaceIds* derivedInterface;
    for (size_t i = 0; i < data->derivedCount; ++i) {
        if (!validateDerivedInterfaceHasValues(loadedDerivedInterfaces[i])) {return 10;}
        data->derivedLengths[i] = loadedDerivedInterfaces[i].size();
        derivedInterface = new DerivedInterfaceIds[data->derivedLengths[i]];
        for (size_t j = 0; j < data->derivedLengths[i]; ++j) {
            if (!validateIdExist(stoul(loadedDerivedInterfaces[i][j][0]), data->count - 1, "Derived interfaces")) {return 11;}
            struct DerivedInterfaceIds derivedInterfaceIds = {stoul(loadedDerivedInterfaces[i][j][0]), stoul(loadedDerivedInterfaces[i][j][1])};
            derivedInterface[j] = derivedInterfaceIds;
        }
        data->derivedList[i] = derivedInterface;
    }
    return 0;
}
int setClockData(struct ClockInfo* data, uint32_t instanceCount, uint32_t interfacesCount)
{
    if (!validateValueDoesNotEqualZero(stoul(loadedClockPeriod), "Clock period")) {return 12;}
    if (!validateValueDoesNotEqualZero(stoul(loadedClockDepth), "Clock depth")) {return 12;}
    data->period = stoul(loadedClockPeriod); // time in nanoseconds
    data->depth = stoul(loadedClockDepth); // number of clock states

    data->strobeUpInstanceList = new uint32_t[instanceCount]; // strobe up order (instance id)
    data->strobeUpInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe up instance (interfaces id)
    data->strobeUpClock = new bool* [instanceCount]; // strobe up activation for instances

    data->strobeDownInstanceList = new uint32_t[instanceCount]; // strobe down order (instance id)
    data->strobeDownInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe down instance (interfaces id)
    data->strobeDownClock = new bool* [instanceCount]; // strobe down activation for instances

    if (!validateValueEqualsNumberOfInstances(loadedStrobeUpInterfaces.size(), loadedStrobeUpInstances.size(), "Strobe up interfaces")) {return 13;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeUpClock.size(), loadedStrobeUpInstances.size(), "Strobe up clock")) {return 13;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeDownInstances.size(), loadedStrobeUpInstances.size(), "Strobe down instances")) {return 13;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeDownInterfaces.size(), loadedStrobeUpInstances.size(), "Strobe down interfaces")) {return 13;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeDownClock.size(), loadedStrobeUpInstances.size(), "Strobe down clock")) {return 13;}
    for (size_t i = 0; i < instanceCount; ++i) {
        if (!validateIdExist(stoul(loadedStrobeUpInstances[i]), instanceCount - 1, "Strobe up instances")) {return 11;}
        if (!validateIdExist(stoul(loadedStrobeUpInterfaces[i]), interfacesCount - 1, "Strobe up interfaces")) {return 11;}
        if (!validateIdExist(stoul(loadedStrobeDownInstances[i]), instanceCount - 1, "Strobe down instances")) {return 11;}
        if (!validateIdExist(stoul(loadedStrobeDownInterfaces[i]), interfacesCount - 1, "Strobe down interfaces")) {return 11;}
        if (!validateVectorSize(loadedStrobeUpClock[i], data->depth, "Strobe up clock")) {return 8;}
        if (!validateVectorSize(loadedStrobeDownClock[i], data->depth, "Strobe down clock")) {return 8;}
        data->strobeUpInstanceList[i] = stoul(loadedStrobeUpInstances[i]);
        data->strobeUpInterfacesList[i] = stoul(loadedStrobeUpInterfaces[i]);
        data->strobeUpClock[i] = new bool[data->depth];
        data->strobeDownInstanceList[i] = stoul(loadedStrobeDownInstances[i]);
        data->strobeDownInterfacesList[i] = stoul(loadedStrobeDownInterfaces[i]);
        data->strobeDownClock[i] = new bool[data->depth];
        for (size_t j = 0; j < data->depth; ++j) {
            data->strobeUpClock[i][j] = stringToBool(loadedStrobeUpClock[i][j]);
            data->strobeDownClock[i][j] = stringToBool(loadedStrobeDownClock[i][j]);
        }
    }
    return 0;
}

void loadConfig(struct Modules* modules, struct InstanceInfo* instanceInfo, struct InterfacesInfo* interfacesInfo, struct ClockInfo* clockInfo){
    loadDataFromFile();
    setInstanceData(modules, instanceInfo);
    setInterfacesData(interfacesInfo, instanceInfo->count);
    setClockData(clockInfo, instanceInfo->count, interfacesInfo->count);
}
