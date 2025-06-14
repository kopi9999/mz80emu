#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "config.hpp"
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

const string configFilePath = "../../config/config.txt";


enum LoadingSteps detectLoadingStep(string row)
{
    for (uint32_t i = 1; i < NUMBER_OF_STEPS; ++i) {
       if (row.rfind(loadingSteps[i], 0) == 0){
            return (enum LoadingSteps) i;
       } 
    }
    return NONE;
}

void loadLineData(
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
            rawInstanceInfo->push_back(row);
            break;
        case INTERFACES:
            rawInterfacesInfo->module.push_back(row);
            break;
        case DERIVED_INTERFACES:
            if (row == "new") {
                rawInterfacesInfo->derived.push_back({});
            } else {
                if (rawInterfacesInfo->derived.size() == 0) {
                    rawInterfacesInfo->derived.push_back({});
                }
                splittedRow = splitByWhitespace(row);
                rawInterfacesInfo->derived[rawInterfacesInfo->derived.size() - 1].push_back(splittedRow);
            }
            break;
        case CLOCK_PERIOD:
            rawClockInfo->period = row;
            break;
        case CLOCK_DEPTH:
            rawClockInfo->depth = row;
            break;
        case STROBE_UP_INSTANCES:
            rawClockInfo->strobeUpInstances.push_back(row);
            break;
        case STROBE_UP_INTERFACES:
            rawClockInfo->strobeUpInterfaces.push_back(row);
            break;
        case STROBE_UP_CLOCK:
            splittedRow = splitByWhitespace(row);
            rawClockInfo->strobeUpClock.push_back(splittedRow);
            break;
        case STROBE_DOWN_INSTANCES:
            rawClockInfo->strobeDownInstances.push_back(row);
            break;
        case STROBE_DOWN_INTERFACES:
            rawClockInfo->strobeDownInterfaces.push_back(row);
            break;
        case STROBE_DOWN_CLOCK:
            splittedRow = splitByWhitespace(row);
            rawClockInfo->strobeDownClock.push_back(splittedRow);
            break;

        case NONE:
            break;
        case NUMBER_OF_STEPS:
            break;
    }
}

enum CrashCode loadRawData( 
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
    ifstream ConfigFile(configFilePath);
    if (!ConfigFile) {
        cout << "ERROR: cannot find config.txt file\n";
        return CONFIG_NOT_FOUND;
    }

    while (getline(ConfigFile, row)) {
        trim(&row);
        loadingStep = detectLoadingStep(row);
        if (loadingStep) {currentLoadingStep = loadingStep;}
        else if (!row.empty()) {
            loadLineData(row, currentLoadingStep, rawModulesInfo, rawInstanceInfo, rawInterfacesInfo, rawClockInfo);
        }
    }

    ConfigFile.close();
    return RUNNING;
}


enum CrashCode validateRawData( 
        vector<string> rawModulesInfo,
        vector<string> rawInstanceInfo,
        struct RawInterfacesInfo rawInterfacesInfo,
        struct RawClockInfo rawClockInfo
        ) {

    enum CrashCode crash = RUNNING;

    if(!validateVectorHasUniqueValues(rawModulesInfo, "Module")) {setCrashIfRunning(&crash, CONFIG_INVALID_MODULE_LIST);}

    for (size_t i = 0; i < rawInstanceInfo.size(); ++i) {
        if (!validateStringIsInteger(rawInstanceInfo[i], "Module instances")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
        else if (!validateIdExist(stoul(rawInstanceInfo[i]), rawModulesInfo.size() - 1, "Module instances")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
    }
    
    for (size_t i = 0; i < rawInterfacesInfo.module.size(); ++i) {
        if (!validateStringIsInteger(rawInterfacesInfo.module[i], "Interfaces")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
        else if (!validateIdExist(stoul(rawInterfacesInfo.module[i]), rawInstanceInfo.size() - 1, "Interfaces")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
    }

    for (size_t i = 0; i < rawInterfacesInfo.derived.size(); ++i) {
        if (!validateDerivedInterfaceHasValues(rawInterfacesInfo.derived[i])) {setCrashIfRunning(&crash, CONFIG_DERIVED_INTERFACE_INVALID);}
        for (size_t j = 0; j < rawInterfacesInfo.derived[i].size(); ++j) {
            if (!validateVectorSize(rawInterfacesInfo.derived[i][j], 2, "Derived interfaces")) {setCrashIfRunning(&crash, CONFIG_INVALID_NUMBER_OF_VALUES);}
            if (!validateStringIsInteger(rawInterfacesInfo.derived[i][j][0], "Derived interfaces")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
            else if (!validateIdExist(stoul(rawInterfacesInfo.derived[i][j][0]), rawInterfacesInfo.module.size() - 1, "Derived interfaces")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
            for (size_t k = 1; k < rawInterfacesInfo.derived[i][j].size(); ++k) {
                if (!validateStringIsInteger(rawInterfacesInfo.derived[i][j][k], "Derived interfaces")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
            }
        }
    }
    
    if (!validateStringIsInteger(rawClockInfo.period, "Clock period")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
    else if (!validateValueDoesNotEqualZero(stoul(rawClockInfo.period), "Clock period")) {setCrashIfRunning(&crash, CONFIG_VALUE_INVALID);}
    if (!validateStringIsInteger(rawClockInfo.depth, "Clock depth")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
    else if (!validateValueDoesNotEqualZero(stoul(rawClockInfo.depth), "Clock depth")) {setCrashIfRunning(&crash, CONFIG_VALUE_INVALID);}

    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeUpInstances.size(), rawInstanceInfo.size(), "Strobe up instances")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeUpInterfaces.size(), rawInstanceInfo.size(), "Strobe up interfaces")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeUpClock.size(), rawInstanceInfo.size(), "Strobe up clock")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeDownInstances.size(), rawInstanceInfo.size(), "Strobe down instances")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeDownInterfaces.size(), rawInstanceInfo.size(), "Strobe down interfaces")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}
    if (!validateValueEqualsNumberOfInstances(rawClockInfo.strobeDownClock.size(), rawInstanceInfo.size(), "Strobe down clock")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}

    if (!validateVectorHasUniqueValues(rawClockInfo.strobeUpInstances, "Strobe up instances")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}
    if (!validateVectorHasUniqueValues(rawClockInfo.strobeDownInstances, "Strobe down instances")) {setCrashIfRunning(&crash, CONFIG_INSTANCE_NUMBER_INCONSISTENT);}

    for (size_t i = 0; i < rawClockInfo.strobeUpInstances.size(); ++i) {
        if (!validateStringIsInteger(rawClockInfo.strobeUpInstances[i], "Strobe up instances")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
        else if (!validateIdExist(stoul(rawClockInfo.strobeUpInstances[i]), rawInstanceInfo.size() - 1, "Strobe up instances")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
    }
    for (size_t i = 0; i < rawClockInfo.strobeUpInterfaces.size(); ++i) {
        if (!validateStringIsInteger(rawClockInfo.strobeUpInterfaces[i], "Strobe up interfaces")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
        else if (!validateIdExist(stoul(rawClockInfo.strobeUpInterfaces[i]), rawInstanceInfo.size() - 1, "Strobe up interfaces")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
    }
    for (size_t i = 0; i < rawClockInfo.strobeDownInstances.size(); ++i) {
        if (!validateStringIsInteger(rawClockInfo.strobeDownInstances[i], "Strobe down clock")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
        else if (!validateIdExist(stoul(rawClockInfo.strobeDownInstances[i]), rawInstanceInfo.size() - 1, "Strobe down instances")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
    }
    for (size_t i = 0; i < rawClockInfo.strobeDownInterfaces.size(); ++i) {
        if (!validateStringIsInteger(rawClockInfo.strobeDownInterfaces[i], "Strobe down interfaces")) {setCrashIfRunning(&crash, CONFIG_VALUE_NAN);}
        else if (!validateIdExist(stoul(rawClockInfo.strobeDownInterfaces[i]), rawInstanceInfo.size() - 1, "Strobe down interfaces")) {setCrashIfRunning(&crash, CONFIG_ID_DOES_NOT_EXIST);}
    }
    for (size_t i = 0; i < rawClockInfo.strobeUpClock.size(); ++i) {
        if (!validateVectorSize(rawClockInfo.strobeUpClock[i], stoul(rawClockInfo.depth), "Strobe up clock")) {setCrashIfRunning(&crash, CONFIG_INVALID_NUMBER_OF_VALUES);}
        for (size_t j = 0; j < rawClockInfo.strobeUpClock[i].size(); ++j) {
            if (!validateStringIsBool(rawClockInfo.strobeUpClock[i][j], "Strobe up clock")) {setCrashIfRunning(&crash, CONFIG_VALUE_NOT_BOOL);}
        }
    }
    for (size_t i = 0; i < rawClockInfo.strobeDownClock.size(); ++i) {
        if (!validateVectorSize(rawClockInfo.strobeDownClock[i], stoul(rawClockInfo.depth), "Strobe down clock")) {setCrashIfRunning(&crash, CONFIG_INVALID_NUMBER_OF_VALUES);}
        for (size_t j = 0; j < rawClockInfo.strobeDownClock[i].size(); ++j) {
            if (!validateStringIsBool(rawClockInfo.strobeDownClock[i][j], "Strobe down clock")) {setCrashIfRunning(&crash, CONFIG_VALUE_NOT_BOOL);}
        }
    }

    return crash;
}


enum CrashCode setInstanceData(struct Modules* modules, struct InstanceInfo* instanceInfo, vector<string> rawModulesInfo, vector<string> rawInstanceInfo)
{
    modules->count = rawModulesInfo.size(); //number of libraries to load
    modules->names = rawModulesInfo;

    instanceInfo->count = rawInstanceInfo.size();
    instanceInfo->list = new uint32_t[instanceInfo->count]; // id`s of libraries for instance creation
    instanceInfo->parameters = new void* [instanceInfo->count]; // pointers to instance parameters (same id as instancesList)
    for (size_t i = 0; i < instanceInfo->count; ++i) {
        instanceInfo->list[i] = stoul(rawInstanceInfo[i]);
        instanceInfo->parameters[i] = NULL;
    }
    return RUNNING;
}

enum CrashCode setInterfacesData(struct InterfacesInfo* data, struct RawInterfacesInfo rawInterfacesInfo)
{
    data->count = rawInterfacesInfo.module.size();
    data->derivedCount = rawInterfacesInfo.derived.size();
    data->totalCount = data->count + data->derivedCount;
    data->list = new uint32_t[data->totalCount]; // id`s of instances for interfaces creation
    data->lengths = new uint16_t[data->count];
    for (size_t i = 0; i < data->count; ++i) {
        data->list[i] = stoul(rawInterfacesInfo.module[i]);
    }

    data->derivedList = new DerivedInterfaceIds*[data->derivedCount];
    data->derivedLengths = new uint16_t[data->derivedCount]; // lengths of all derived interfaces tables
    DerivedInterfaceIds* derivedInterface;
    for (size_t i = 0; i < data->derivedCount; ++i) {
        data->derivedLengths[i] = rawInterfacesInfo.derived[i].size();
        derivedInterface = new DerivedInterfaceIds[data->derivedLengths[i]];
        for (size_t j = 0; j < data->derivedLengths[i]; ++j) {
            struct DerivedInterfaceIds derivedInterfaceIds = {stoul(rawInterfacesInfo.derived[i][j][0]), stoul(rawInterfacesInfo.derived[i][j][1])};
            derivedInterface[j] = derivedInterfaceIds;
        }
        data->derivedList[i] = derivedInterface;
    }
    return RUNNING;
}

enum CrashCode setClockData(struct ClockInfo* data, uint32_t instanceCount, struct RawClockInfo rawClockInfo)
{
    data->period = stoul(rawClockInfo.period); // time in nanoseconds
    data->depth = stoul(rawClockInfo.depth); // number of clock states

    data->strobeUpInstanceList = new uint32_t[instanceCount]; // strobe up order (instance id)
    data->strobeUpInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe up instance (interfaces id)
    data->strobeUpClock = new bool* [instanceCount]; // strobe up activation for instances

    data->strobeDownInstanceList = new uint32_t[instanceCount]; // strobe down order (instance id)
    data->strobeDownInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe down instance (interfaces id)
    data->strobeDownClock = new bool* [instanceCount]; // strobe down activation for instances

    for (size_t i = 0; i < instanceCount; ++i) {
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

enum CrashCode rawDataToInfo(
        struct Modules* modules,
        struct InstanceInfo* instanceInfo,
        struct InterfacesInfo* interfacesInfo,
        struct ClockInfo* clockInfo,
        vector<string> rawModulesInfo,
        vector<string> rawInstanceInfo,
        struct RawInterfacesInfo rawInterfacesInfo,
        struct RawClockInfo rawClockInfo
        )
{
    enum CrashCode crash;

    crash = setInstanceData(modules, instanceInfo, rawModulesInfo, rawInstanceInfo);
    if (crash) {cout << "CRITICAL: Setting instance data from config file failed.\n"; return crash;}
    
    crash = setInterfacesData(interfacesInfo, rawInterfacesInfo);
    if (crash) {cout << "CRITICAL: Setting interfaces data from config file failed.\n"; return crash;}
    
    crash = setClockData(clockInfo, instanceInfo->count, rawClockInfo);
    if (crash) {cout << "CRITICAL: Setting clock data from config file failed.\n"; return crash;}

    return RUNNING;
}


void setRawInstanceData(vector<string>* rawModulesInfo, vector<string>* rawInstanceInfo, struct Modules modules, struct InstanceInfo instanceInfo)
{
    *rawModulesInfo = modules.names;

    for (size_t i = 0; i < instanceInfo.count; ++i) {
        rawInstanceInfo->push_back(to_string(instanceInfo.list[i]));
    }
}

void setRawInterfacesData(struct RawInterfacesInfo* rawInterfacesInfo, struct InterfacesInfo data)
{
    for (size_t i = 0; i < data.count; ++i) {
        rawInterfacesInfo->module.push_back(to_string(data.list[i]));
    }
    
    for (size_t i = 0; i < data.derivedCount; ++i) {
        rawInterfacesInfo->derived.push_back({});
        for (size_t j = 0; j < data.derivedLengths[i]; ++j) {
            rawInterfacesInfo->derived[i].push_back({});
            rawInterfacesInfo->derived[i][j].push_back(to_string(data.derivedList[i][j].interfacesId));
            rawInterfacesInfo->derived[i][j].push_back(to_string(data.derivedList[i][j].interfaceId));
        }
    }
}

void setRawClockData(struct RawClockInfo* rawClockInfo, struct ClockInfo data, uint32_t instanceCount)
{
    rawClockInfo->period = to_string(data.period);
    rawClockInfo->depth = to_string(data.depth);

    for (size_t i = 0; i < instanceCount; ++i) {
        rawClockInfo->strobeUpInstances.push_back(to_string(data.strobeUpInstanceList[i]));
        rawClockInfo->strobeUpInterfaces.push_back(to_string(data.strobeUpInterfacesList[i]));
        rawClockInfo->strobeDownInstances.push_back(to_string(data.strobeDownInstanceList[i]));
        rawClockInfo->strobeDownInterfaces.push_back(to_string(data.strobeDownInterfacesList[i]));
        rawClockInfo->strobeUpClock.push_back({});
        rawClockInfo->strobeDownClock.push_back({});
        for (size_t j = 0; j < data.depth; ++j) {
            rawClockInfo->strobeUpClock[i].push_back(boolToString(data.strobeUpClock[i][j]));
            rawClockInfo->strobeDownClock[i].push_back(boolToString(data.strobeDownClock[i][j]));
        }
    }
}

void infoToRawData(
        vector<string>* rawModulesInfo,
        vector<string>* rawInstanceInfo,
        struct RawInterfacesInfo* rawInterfacesInfo,
        struct RawClockInfo* rawClockInfo,
        struct Modules modules,
        struct InstanceInfo instanceInfo,
        struct InterfacesInfo interfacesInfo,
        struct ClockInfo clockInfo
        )
{
    setRawInstanceData(rawModulesInfo, rawInstanceInfo, modules, instanceInfo);
    setRawInterfacesData(rawInterfacesInfo, interfacesInfo);
    setRawClockData(rawClockInfo, clockInfo, instanceInfo.count);
}


enum CrashCode rawDataToFile(vector<string> rawModulesInfo, vector<string> rawInstanceInfo, struct RawInterfacesInfo rawInterfacesInfo, struct RawClockInfo rawClockInfo) {
    ofstream ConfigFile(configFilePath);
    if (!ConfigFile) {
        cout << "ERROR: cannot open config.txt file\n";
        return CONFIG_NOT_OPENED;
    }

    ConfigFile << loadingSteps[MODULES] << ":" << endl;
    for (size_t i = 0; i < rawModulesInfo.size(); ++i) {
        ConfigFile << rawModulesInfo[i] << endl;
    }

    ConfigFile << endl << loadingSteps[MODULE_INSTANCES] << ":" << endl;
    for (size_t i = 0; i < rawInstanceInfo.size(); ++i) {
        ConfigFile << rawInstanceInfo[i] << endl;
    }

    ConfigFile << endl << loadingSteps[INTERFACES] << ":" << endl;
    for (size_t i = 0; i < rawInterfacesInfo.module.size(); ++i) {
        ConfigFile << rawInterfacesInfo.module[i] << endl;
    }

    ConfigFile << endl << loadingSteps[DERIVED_INTERFACES] << ":" << endl;
    for (size_t i = 0; i < rawInterfacesInfo.derived.size(); ++i) {
        ConfigFile << "new" << endl;
        for (size_t j = 0; j < rawInterfacesInfo.derived[i].size(); ++j) {
            ConfigFile << rawInterfacesInfo.derived[i][j][0] << " " << rawInterfacesInfo.derived[i][j][1] << endl;
        }
    }

    ConfigFile << endl << loadingSteps[CLOCK_PERIOD] << ":" << endl;
    ConfigFile << rawClockInfo.period << endl;
    ConfigFile << endl << loadingSteps[CLOCK_DEPTH] << ":" << endl;
    ConfigFile << rawClockInfo.depth << endl;

    ConfigFile << endl << loadingSteps[STROBE_UP_INSTANCES] << ":" << endl;
    for (size_t i = 0; i < rawClockInfo.strobeUpInstances.size(); ++i) {
        ConfigFile << rawClockInfo.strobeUpInstances[i] << endl;
    }

    ConfigFile << endl << loadingSteps[STROBE_UP_INTERFACES] << ":" << endl;
    for (size_t i = 0; i < rawClockInfo.strobeUpInterfaces.size(); ++i) {
        ConfigFile << rawClockInfo.strobeUpInterfaces[i] << endl;
    }

    ConfigFile << endl << loadingSteps[STROBE_UP_CLOCK] << ":" << endl;
    for (size_t i = 0; i < rawClockInfo.strobeUpClock.size(); ++i) {
        for (size_t j = 0; j < rawClockInfo.strobeUpClock[i].size(); ++j) {
            ConfigFile << rawClockInfo.strobeUpClock[i][j];
            if (j == rawClockInfo.strobeUpClock[i].size() - 1) {
                ConfigFile << endl;
            } else {
                ConfigFile << " ";
            }
        }
    }

    ConfigFile << endl << loadingSteps[STROBE_DOWN_INSTANCES] << ":" << endl;
    for (size_t i = 0; i < rawClockInfo.strobeDownInstances.size(); ++i) {
        ConfigFile << rawClockInfo.strobeDownInstances[i] << endl;
    }

    ConfigFile << endl << loadingSteps[STROBE_DOWN_INTERFACES] << ":" << endl;
    for (size_t i = 0; i < rawClockInfo.strobeDownInterfaces.size(); ++i) {
        ConfigFile << rawClockInfo.strobeDownInterfaces[i] << endl;
    }

    ConfigFile << endl << loadingSteps[STROBE_DOWN_CLOCK] << ":" << endl;
    for (size_t i = 0; i < rawClockInfo.strobeDownClock.size(); ++i) {
        for (size_t j = 0; j < rawClockInfo.strobeDownClock[i].size(); ++j) {
            ConfigFile << rawClockInfo.strobeDownClock[i][j];
            if (j == rawClockInfo.strobeDownClock[i].size() - 1) {
                ConfigFile << endl;
            } else {
                ConfigFile << " ";
            }
        }
    }
}


enum CrashCode loadConfig(struct Modules* modules, struct InstanceInfo* instanceInfo, struct InterfacesInfo* interfacesInfo, struct ClockInfo* clockInfo){
    enum CrashCode crash;
    vector<string> rawModulesInfo;
    vector<string> rawInstanceInfo;
    struct RawInterfacesInfo rawInterfacesInfo = {};
    struct RawClockInfo rawClockInfo = {};

    crash = loadRawData(&rawModulesInfo, &rawInstanceInfo, &rawInterfacesInfo, &rawClockInfo);
    if (crash) {cout << "CRITICAL: Loading data from config file failed.\n"; return crash;}

    crash = validateRawData(rawModulesInfo, rawInstanceInfo, rawInterfacesInfo, rawClockInfo);
    if (crash) {cout << "CRITICAL: Bad config file.\n"; return crash;}

    crash = rawDataToInfo(modules, instanceInfo, interfacesInfo, clockInfo, rawModulesInfo, rawInstanceInfo, rawInterfacesInfo, rawClockInfo);
    if (crash) {return crash;}

    return RUNNING;
}
