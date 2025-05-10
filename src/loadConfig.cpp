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

enum CrashCode loadLineData(string row, enum LoadingSteps currentLoadingStep)
{
    vector<string> splittedRow;
    switch (currentLoadingStep){
        case MODULES:
            loadedModules.push_back(row);
            break;
        case MODULE_INSTANCES:
            if (!validateStringIsInteger(row, "Module instances")) {return CONFIG_VALUE_NAN;}
            loadedModuleInstances.push_back(row);
            break;
        case INTERFACES:
            if (!validateStringIsInteger(row, "Interfaces")) {return CONFIG_VALUE_NAN;}
            loadedInterfaces.push_back(row);
            break;
        case DERIVED_INTERFACES:
            if (row == "new") {
                loadedDerivedInterfaces.push_back({});
            } else {
                if (!validateDerivedInterfaceCreated(loadedDerivedInterfaces)) {return CONFIG_DERIVED_INTERFACE_INVALID;}
                splittedRow = splitByWhitespace(row);
                if (!validateVectorSize(splittedRow, 2, "Derived interfaces")) {return CONFIG_TOO_MANY_VALUES;}
                if (!validateStringIsInteger(splittedRow[0], "Derived interfaces") || !validateStringIsInteger(splittedRow[1], "Derived interfaces")) {return CONFIG_VALUE_NAN;}
                loadedDerivedInterfaces[loadedDerivedInterfaces.size() - 1].push_back(splittedRow);
            }
            break;
        case CLOCK_PERIOD:
            if (!validateStringIsInteger(row, "Clock period")) {return CONFIG_VALUE_NAN;}
            loadedClockPeriod = row;
            break;
        case CLOCK_DEPTH:
            if (!validateStringIsInteger(row, "Clock depth")) {return CONFIG_VALUE_NAN;}
            loadedClockDepth = row;
            break;
        case STROBE_UP_INSTANCES:
            if (!validateStringIsInteger(row, "Strobe up instances")) {return CONFIG_VALUE_NAN;}
            loadedStrobeUpInstances.push_back(row);
            break;
        case STROBE_UP_INTERFACES:
            if (!validateStringIsInteger(row, "Strobe up interfaces")) {return CONFIG_VALUE_NAN;}
            loadedStrobeUpInterfaces.push_back(row);
            break;
        case STROBE_UP_CLOCK:
            splittedRow = splitByWhitespace(row);
            for (int i=0; i<splittedRow.size(); i++) {
                if (!validateStringIsBool(splittedRow[i], "Strobe up clock")) {return CONFIG_VALUE_NOT_BOOL;}
            }
            loadedStrobeUpClock.push_back(splittedRow);
            break;
        case STROBE_DOWN_INSTANCES:
            if (!validateStringIsInteger(row, "Strobe down clock")) {return CONFIG_VALUE_NAN;}
            loadedStrobeDownInstances.push_back(row);
            break;
        case STROBE_DOWN_INTERFACES:
            if (!validateStringIsInteger(row, "Strobe down interfaces")) {return CONFIG_VALUE_NAN;}
            loadedStrobeDownInterfaces.push_back(row);
            break;
        case STROBE_DOWN_CLOCK:
            splittedRow = splitByWhitespace(row);
            for (int i=0; i<splittedRow.size(); i++) {
                if (!validateStringIsBool(splittedRow[i], "Strobe down clock")) {return CONFIG_VALUE_NOT_BOOL;}
            }
            loadedStrobeDownClock.push_back(splittedRow);
            break;

        case NONE:
            break;
        case NUMBER_OF_STEPS:
            break;
    }
    return RUNNING;
}

enum CrashCode loadDataFromFile() 
{
    enum LoadingSteps currentLoadingStep = NONE;
    enum LoadingSteps loadingStep = NONE;
    bool loadingStepChange;
    string row;
    ifstream ConfigFile("../../config/config.txt");
    if (!ConfigFile) {
        cout << "ERROR: cannot find config.txt file\n";
        return CONFIG_NOT_FOUND;
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
    return RUNNING;
}

enum CrashCode setInstanceData(struct Modules* modules, struct InstanceInfo* instanceInfo)
{
    modules->count = loadedModules.size(); //number of libraries to load
    modules->names = loadedModules;

    instanceInfo->count = loadedModuleInstances.size();
    instanceInfo->list = new uint32_t[instanceInfo->count]; // id`s of libraries for instance creation
    instanceInfo->parameters = new void* [instanceInfo->count]; // pointers to instance parameters (same id as instancesList)
    for (size_t i = 0; i < instanceInfo->count; ++i) {
        if (!validateIdExist(stoul(loadedModuleInstances[i]), modules->count - 1, "Module instances")) {return CONFIG_ID_DOES_NOT_EXIST;}
        instanceInfo->list[i] = stoul(loadedModuleInstances[i]);
        instanceInfo->parameters[i] = NULL;
    }
    return RUNNING;
}

enum CrashCode setInterfacesData(struct InterfacesInfo* data, uint32_t instanceCount)
{
    data->count = loadedInterfaces.size();
    data->derivedCount = loadedDerivedInterfaces.size();
    data->totalCount = data->count + data->derivedCount;
    data->list = new uint32_t[data->totalCount]; // id`s of instances for interfaces creation
    data->lengths = new uint16_t[data->count];
    for (size_t i = 0; i < data->count; ++i) {
        if (!validateIdExist(stoul(loadedInterfaces[i]), instanceCount - 1, "Interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
        data->list[i] = stoul(loadedInterfaces[i]);
    }

    data->derivedList = new DerivedInterfaceIds*[data->derivedCount];
    data->derivedLengths = new uint16_t[data->derivedCount]; // lengths of all derived interfaces tables
    DerivedInterfaceIds* derivedInterface;
    for (size_t i = 0; i < data->derivedCount; ++i) {
        if (!validateDerivedInterfaceHasValues(loadedDerivedInterfaces[i])) {return CONFIG_DERIVED_INTERFACE_INVALID;}
        data->derivedLengths[i] = loadedDerivedInterfaces[i].size();
        derivedInterface = new DerivedInterfaceIds[data->derivedLengths[i]];
        for (size_t j = 0; j < data->derivedLengths[i]; ++j) {
            if (!validateIdExist(stoul(loadedDerivedInterfaces[i][j][0]), data->count - 1, "Derived interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
            struct DerivedInterfaceIds derivedInterfaceIds = {stoul(loadedDerivedInterfaces[i][j][0]), stoul(loadedDerivedInterfaces[i][j][1])};
            derivedInterface[j] = derivedInterfaceIds;
        }
        data->derivedList[i] = derivedInterface;
    }
    return RUNNING;
}
enum CrashCode setClockData(struct ClockInfo* data, uint32_t instanceCount, uint32_t interfacesCount)
{
    if (!validateValueDoesNotEqualZero(stoul(loadedClockPeriod), "Clock period")) {return CONFIG_VALUE_INVALID;}
    if (!validateValueDoesNotEqualZero(stoul(loadedClockDepth), "Clock depth")) {return CONFIG_VALUE_INVALID;}
    data->period = stoul(loadedClockPeriod); // time in nanoseconds
    data->depth = stoul(loadedClockDepth); // number of clock states

    data->strobeUpInstanceList = new uint32_t[instanceCount]; // strobe up order (instance id)
    data->strobeUpInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe up instance (interfaces id)
    data->strobeUpClock = new bool* [instanceCount]; // strobe up activation for instances

    data->strobeDownInstanceList = new uint32_t[instanceCount]; // strobe down order (instance id)
    data->strobeDownInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe down instance (interfaces id)
    data->strobeDownClock = new bool* [instanceCount]; // strobe down activation for instances

    if (!validateValueEqualsNumberOfInstances(loadedStrobeUpInterfaces.size(), loadedStrobeUpInstances.size(), "Strobe up interfaces")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeUpClock.size(), loadedStrobeUpInstances.size(), "Strobe up clock")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeDownInstances.size(), loadedStrobeUpInstances.size(), "Strobe down instances")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeDownInterfaces.size(), loadedStrobeUpInstances.size(), "Strobe down interfaces")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(loadedStrobeDownClock.size(), loadedStrobeUpInstances.size(), "Strobe down clock")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    for (size_t i = 0; i < instanceCount; ++i) {
        if (!validateIdExist(stoul(loadedStrobeUpInstances[i]), instanceCount - 1, "Strobe up instances")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateIdExist(stoul(loadedStrobeUpInterfaces[i]), interfacesCount - 1, "Strobe up interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateIdExist(stoul(loadedStrobeDownInstances[i]), instanceCount - 1, "Strobe down instances")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateIdExist(stoul(loadedStrobeDownInterfaces[i]), interfacesCount - 1, "Strobe down interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateVectorSize(loadedStrobeUpClock[i], data->depth, "Strobe up clock")) {return CONFIG_INVALID_NUMBER_OF_VALUES;}
        if (!validateVectorSize(loadedStrobeDownClock[i], data->depth, "Strobe down clock")) {return CONFIG_INVALID_NUMBER_OF_VALUES;}
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
    return RUNNING;
}

enum CrashCode loadConfig(struct Modules* modules, struct InstanceInfo* instanceInfo, struct InterfacesInfo* interfacesInfo, struct ClockInfo* clockInfo){
    loadDataFromFile();
    setInstanceData(modules, instanceInfo);
    setInterfacesData(interfacesInfo, instanceInfo->count);
    setClockData(clockInfo, instanceInfo->count, interfacesInfo->count);
    return RUNNING;
}
