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

struct RawInterfacesInfo {
    vector<string> module;
    vector<vector<vector<string>>> derived;
};

struct RawClockInfo {
    string period;
    string depth;
    vector<string> strobeUpInstances;
    vector<string> strobeUpInterfaces;
    vector<vector<string>> strobeUpClock;
    vector<string> strobeDownInstances;
    vector<string> strobeDownInterfaces;
    vector<vector<string>> strobeDownClock;
};


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

enum CrashCode loadLineData(
        string row,
        enum LoadingSteps currentLoadingStep,
        vector<string>* rawModulesInfo,
        vector<string>* rawInstanceInfo,
        struct RawInterfacesInfo* rawInterfacesInfo,
        struct RawClockInfo* rawClockInfo
        )
{
    vector<string> splittedRow;
    switch (currentLoadingStep){
        case MODULES:
            rawModulesInfo->push_back(row);
            break;
        case MODULE_INSTANCES:
            if (!validateStringIsInteger(row, "Module instances")) {return CONFIG_VALUE_NAN;}
            rawInstanceInfo->push_back(row);
            break;
        case INTERFACES:
            if (!validateStringIsInteger(row, "Interfaces")) {return CONFIG_VALUE_NAN;}
            rawInterfacesInfo->module.push_back(row);
            break;
        case DERIVED_INTERFACES:
            if (row == "new") {
                rawInterfacesInfo->derived.push_back({});
            } else {
                if (!validateDerivedInterfaceCreated(rawInterfacesInfo->derived)) {return CONFIG_DERIVED_INTERFACE_INVALID;}
                splittedRow = splitByWhitespace(row);
                if (!validateVectorSize(splittedRow, 2, "Derived interfaces")) {return CONFIG_INVALID_NUMBER_OF_VALUES;}
                if (!validateStringIsInteger(splittedRow[0], "Derived interfaces") || !validateStringIsInteger(splittedRow[1], "Derived interfaces")) {return CONFIG_VALUE_NAN;}
                rawInterfacesInfo->derived[rawInterfacesInfo->derived.size() - 1].push_back(splittedRow);
            }
            break;
        case CLOCK_PERIOD:
            if (!validateStringIsInteger(row, "Clock period")) {return CONFIG_VALUE_NAN;}
            rawClockInfo->period = row;
            break;
        case CLOCK_DEPTH:
            if (!validateStringIsInteger(row, "Clock depth")) {return CONFIG_VALUE_NAN;}
            rawClockInfo->depth = row;
            break;
        case STROBE_UP_INSTANCES:
        if (!validateStringIsInteger(row, "Strobe up instances")) {return CONFIG_VALUE_NAN;}
            rawClockInfo->strobeUpInstances.push_back(row);
            break;
        case STROBE_UP_INTERFACES:
            if (!validateStringIsInteger(row, "Strobe up interfaces")) {return CONFIG_VALUE_NAN;}
            rawClockInfo->strobeUpInterfaces.push_back(row);
            break;
        case STROBE_UP_CLOCK:
            splittedRow = splitByWhitespace(row);
            for (int i=0; i<splittedRow.size(); i++) {
                if (!validateStringIsBool(splittedRow[i], "Strobe up clock")) {return CONFIG_VALUE_NOT_BOOL;}
            }
            rawClockInfo->strobeUpClock.push_back(splittedRow);
            break;
        case STROBE_DOWN_INSTANCES:
            if (!validateStringIsInteger(row, "Strobe down clock")) {return CONFIG_VALUE_NAN;}
            rawClockInfo->strobeDownInstances.push_back(row);
            break;
        case STROBE_DOWN_INTERFACES:
            if (!validateStringIsInteger(row, "Strobe down interfaces")) {return CONFIG_VALUE_NAN;}
            rawClockInfo->strobeDownInterfaces.push_back(row);
            break;
        case STROBE_DOWN_CLOCK:
            splittedRow = splitByWhitespace(row);
            for (int i=0; i<splittedRow.size(); i++) {
                if (!validateStringIsBool(splittedRow[i], "Strobe down clock")) {return CONFIG_VALUE_NOT_BOOL;}
            }
            rawClockInfo->strobeDownClock.push_back(splittedRow);
            break;

        case NONE:
            break;
        case NUMBER_OF_STEPS:
            break;
    }
    return RUNNING;
}

enum CrashCode loadDataFromFile( 
        vector<string>* rawModulesInfo,
        vector<string>* rawInstanceInfo,
        struct RawInterfacesInfo* rawInterfacesInfo,
        struct RawClockInfo* rawClockInfo
        )
{
    enum CrashCode crash = RUNNING;
    enum LoadingSteps currentLoadingStep = NONE;
    enum LoadingSteps loadingStep = NONE;
    string row;
    ifstream ConfigFile("../../config/config.txt");
    if (!ConfigFile) {
        cout << "ERROR: cannot find config.txt file\n";
        return CONFIG_NOT_FOUND;
    }

    while (getline(ConfigFile, row)) {
        trim(&row);
        loadingStep = detectLoadingStep(row);
        if (loadingStep) {currentLoadingStep = loadingStep;}
        else if (!row.empty()) {
            crash = loadLineData(row, currentLoadingStep, rawModulesInfo, rawInstanceInfo, rawInterfacesInfo, rawClockInfo);
            if (crash) {break;}
        }
    }

    ConfigFile.close();
    return crash;
}

enum CrashCode setInstanceData(struct Modules* modules, struct InstanceInfo* instanceInfo, vector<string> rawModulesInfo, vector<string> rawInstanceInfo)
{
    if(!validateVectorHasUniqueValues(rawModulesInfo, "Module")) {return CONFIG_INVALID_MODULE_LIST;}
    modules->count = rawModulesInfo.size(); //number of libraries to load
    modules->names = rawModulesInfo;

    instanceInfo->count = rawInstanceInfo.size();
    instanceInfo->list = new uint32_t[instanceInfo->count]; // id`s of libraries for instance creation
    instanceInfo->parameters = new void* [instanceInfo->count]; // pointers to instance parameters (same id as instancesList)
    for (size_t i = 0; i < instanceInfo->count; ++i) {
        if (!validateIdExist(stoul(rawInstanceInfo[i]), modules->count - 1, "Module instances")) {return CONFIG_ID_DOES_NOT_EXIST;}
        instanceInfo->list[i] = stoul(rawInstanceInfo[i]);
        instanceInfo->parameters[i] = NULL;
    }
    return RUNNING;
}

enum CrashCode setInterfacesData(struct InterfacesInfo* data, uint32_t instanceCount, struct RawInterfacesInfo rawInterfacesInfo)
{
    data->count = rawInterfacesInfo.module.size();
    data->derivedCount = rawInterfacesInfo.derived.size();
    data->totalCount = data->count + data->derivedCount;
    data->list = new uint32_t[data->totalCount]; // id`s of instances for interfaces creation
    data->lengths = new uint16_t[data->count];
    for (size_t i = 0; i < data->count; ++i) {
        if (!validateIdExist(stoul(rawInterfacesInfo.module[i]), instanceCount - 1, "Interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
        data->list[i] = stoul(rawInterfacesInfo.module[i]);
    }

    data->derivedList = new DerivedInterfaceIds*[data->derivedCount];
    data->derivedLengths = new uint16_t[data->derivedCount]; // lengths of all derived interfaces tables
    DerivedInterfaceIds* derivedInterface;
    for (size_t i = 0; i < data->derivedCount; ++i) {
        if (!validateDerivedInterfaceHasValues(rawInterfacesInfo.derived[i])) {return CONFIG_DERIVED_INTERFACE_INVALID;}
        data->derivedLengths[i] = rawInterfacesInfo.derived[i].size();
        derivedInterface = new DerivedInterfaceIds[data->derivedLengths[i]];
        for (size_t j = 0; j < data->derivedLengths[i]; ++j) {
            if (!validateIdExist(stoul(rawInterfacesInfo.derived[i][j][0]), data->count - 1, "Derived interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
            struct DerivedInterfaceIds derivedInterfaceIds = {stoul(rawInterfacesInfo.derived[i][j][0]), stoul(rawInterfacesInfo.derived[i][j][1])};
            derivedInterface[j] = derivedInterfaceIds;
        }
        data->derivedList[i] = derivedInterface;
    }
    return RUNNING;
}
enum CrashCode setClockData(struct ClockInfo* data, uint32_t instanceCount, uint32_t interfacesCount, struct RawClockInfo rawClockInfo)
{
    if (!validateValueDoesNotEqualZero(stoul(rawClockInfo.period), "Clock period")) {return CONFIG_VALUE_INVALID;}
    if (!validateValueDoesNotEqualZero(stoul(rawClockInfo.depth), "Clock depth")) {return CONFIG_VALUE_INVALID;}
    data->period = stoul(rawClockInfo.period); // time in nanoseconds
    data->depth = stoul(rawClockInfo.depth); // number of clock states

    data->strobeUpInstanceList = new uint32_t[instanceCount]; // strobe up order (instance id)
    data->strobeUpInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe up instance (interfaces id)
    data->strobeUpClock = new bool* [instanceCount]; // strobe up activation for instances

    data->strobeDownInstanceList = new uint32_t[instanceCount]; // strobe down order (instance id)
    data->strobeDownInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe down instance (interfaces id)
    data->strobeDownClock = new bool* [instanceCount]; // strobe down activation for instances

    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeUpInstances.size(), instanceCount, "Strobe up instances")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeUpInterfaces.size(), rawClockInfo.strobeUpInstances.size(), "Strobe up interfaces")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeUpClock.size(), rawClockInfo.strobeUpInstances.size(), "Strobe up clock")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}

    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeDownInstances.size(), instanceCount, "Strobe down instances")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeDownInterfaces.size(), rawClockInfo.strobeUpInstances.size(), "Strobe down interfaces")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeDownClock.size(), rawClockInfo.strobeUpInstances.size(), "Strobe down clock")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}

    if (!validateVectorHasUniqueValues(rawClockInfo.strobeUpInstances, "Strobe up instances")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    if (!validateVectorHasUniqueValues(rawClockInfo.strobeDownInstances, "Strobe down instances")) {return CONFIG_INSTANCE_NUMBER_INCONSISTENT;}
    for (size_t i = 0; i < instanceCount; ++i) {
        if (!validateIdExist(stoul(rawClockInfo.strobeUpInstances[i]), instanceCount - 1, "Strobe up instances")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateIdExist(stoul(rawClockInfo.strobeUpInterfaces[i]), interfacesCount - 1, "Strobe up interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateIdExist(stoul(rawClockInfo.strobeDownInstances[i]), instanceCount - 1, "Strobe down instances")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateIdExist(stoul(rawClockInfo.strobeDownInterfaces[i]), interfacesCount - 1, "Strobe down interfaces")) {return CONFIG_ID_DOES_NOT_EXIST;}
        if (!validateVectorSize(rawClockInfo.strobeUpClock[i], data->depth, "Strobe up clock")) {return CONFIG_INVALID_NUMBER_OF_VALUES;}
        if (!validateVectorSize(rawClockInfo.strobeDownClock[i], data->depth, "Strobe down clock")) {return CONFIG_INVALID_NUMBER_OF_VALUES;}
        data->strobeUpInstanceList[i] = stoul(rawClockInfo.strobeUpInstances[i]);
        data->strobeUpInterfacesList[i] = stoul(rawClockInfo.strobeUpInterfaces[i]);
        data->strobeUpClock[i] = new bool[data->depth];
        data->strobeDownInstanceList[i] = stoul(rawClockInfo.strobeDownInstances[i]);
        data->strobeDownInterfacesList[i] = stoul(rawClockInfo.strobeDownInterfaces[i]);
        data->strobeDownClock[i] = new bool[data->depth];
        for (size_t j = 0; j < data->depth; ++j) {
            data->strobeUpClock[i][j] = stringToBool(rawClockInfo.strobeUpClock[i][j]);
            data->strobeDownClock[i][j] = stringToBool(rawClockInfo.strobeDownClock[i][j]);
        }
    }
    return RUNNING;
}

enum CrashCode loadConfig(struct Modules* modules, struct InstanceInfo* instanceInfo, struct InterfacesInfo* interfacesInfo, struct ClockInfo* clockInfo){
    enum CrashCode crash;
    vector<string> rawModulesInfo;
    vector<string> rawInstanceInfo;
    struct RawInterfacesInfo rawInterfacesInfo = {};
    struct RawClockInfo rawClockInfo = {};


    crash = loadDataFromFile(&rawModulesInfo, &rawInstanceInfo, &rawInterfacesInfo, &rawClockInfo);
    if (crash) {cout << "CRITICAL: Bad config file.\n"; return crash;}

    crash = setInstanceData(modules, instanceInfo, rawModulesInfo, rawInstanceInfo);
    if (crash) {cout << "CRITICAL: Bad config file.\n"; return crash;}
    
    crash = setInterfacesData(interfacesInfo, instanceInfo->count, rawInterfacesInfo);
    if (crash) {cout << "CRITICAL: Bad config file.\n"; return crash;}
    
    crash = setClockData(clockInfo, instanceInfo->count, interfacesInfo->count, rawClockInfo);
    if (crash) {cout << "CRITICAL: Bad config file.\n"; return crash;}

    return RUNNING;
}
