#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "loadConfig.hpp"
#include "validation.hpp"
#include "main.hpp"
#include "misc.hpp"

using namespace std;

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



uint32_t instanceCount;
uint32_t* instancesList;
void** instancesParameters;

uint32_t interfacesCount;
uint32_t derivedInterfacesCount;
uint32_t totalInterfacesCount;
uint32_t* interfacesList;
DerivedInterfaceIds** derivedInterfacesList;
uint32_t* derivedInterfacesLengths;

uint32_t clockPeriod;
uint32_t clockDepth;

uint32_t* strobeUpInstanceList;
uint32_t* strobeUpInterfacesList;
bool** strobeUpClock;
uint32_t* strobeDownInstanceList;
uint32_t* strobeDownInterfacesList;
bool** strobeDownClock;

int loadDataFromFile() 
{
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
    vector<string> splittedRow;
    ifstream ConfigFile("../../config/config.txt");
    if (!ConfigFile) {
        cout << "ERROR: cannot find config.txt file\n";
        return 5;
    }

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
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedModuleInstances.push_back(row);
            }
            else if (currentLoadingStep == "Interfaces") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedInterfaces.push_back(row);
            }
            else if (currentLoadingStep == "Derived interfaces") {
                if (row == "new") {
                    loadedDerivedInterfaces.push_back({});
                }
                else {
                    if (!validateDerivedInterfaceCreated(loadedDerivedInterfaces)) {return 9;}
                    splittedRow = splitByWhitespace(row);
                    if (!validateVectorSize(splittedRow, 2, currentLoadingStep)) {return 8;}
                    if (!validateStringIsInteger(splittedRow[0], currentLoadingStep) || !validateStringIsInteger(splittedRow[1], currentLoadingStep)) {return 6;}
                    loadedDerivedInterfaces[loadedDerivedInterfaces.size() - 1].push_back(splittedRow);
                }
            }
            else if (currentLoadingStep == "Clock period") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedClockPeriod = row;
            }
            else if (currentLoadingStep == "Clock depth") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedClockDepth = row;
            }
            else if (currentLoadingStep == "Strobe up instances") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedStrobeUpInstances.push_back(row);
            }
            else if (currentLoadingStep == "Strobe up interfaces") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedStrobeUpInterfaces.push_back(row);
            }
            else if (currentLoadingStep == "Strobe up clock") {
                splittedRow = splitByWhitespace(row);
                for (int i=0; i<splittedRow.size(); i++) {
                    if (!validateStringIsBool(splittedRow[i], currentLoadingStep)) {return 7;}
                }
                loadedStrobeUpClock.push_back(splittedRow);
            }
            else if (currentLoadingStep == "Strobe down instances") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedStrobeDownInstances.push_back(row);
            }
            else if (currentLoadingStep == "Strobe down interfaces") {
                if (!validateStringIsInteger(row, currentLoadingStep)) {return 6;}
                loadedStrobeDownInterfaces.push_back(row);
            }
            else if (currentLoadingStep == "Strobe down clock") {
                splittedRow = splitByWhitespace(row);
                for (int i=0; i<splittedRow.size(); i++) {
                    if (!validateStringIsBool(splittedRow[i], currentLoadingStep)) {return 7;}
                }
                loadedStrobeDownClock.push_back(splittedRow);
            }
        }
    }

    ConfigFile.close();
    return 0;
}


int processRawData()
{
    modules.count = loadedModules.size(); //number of libraries to load
    modules.names = loadedModules;

    instanceCount = loadedModuleInstances.size();
    instancesList = new uint32_t[instanceCount]; // id`s of libraries for instance creation
    instancesParameters = new void* [instanceCount]; // pointers to instance parameters (same id as instancesList)
    for (size_t i = 0; i < instanceCount; ++i) {
        if (!validateIdExist(stoul(loadedModuleInstances[i]), modules.count - 1, "Module instances")) {return 11;}
        instancesList[i] = stoul(loadedModuleInstances[i]);
        instancesParameters[i] = NULL;
    }

    interfacesCount = loadedInterfaces.size();
    derivedInterfacesCount = loadedDerivedInterfaces.size();
    totalInterfacesCount = interfacesCount + derivedInterfacesCount;
    interfacesList = new uint32_t[totalInterfacesCount]; // id`s of instances for interfaces creation
    for (size_t i = 0; i < interfacesCount; ++i) {
        if (!validateIdExist(stoul(loadedInterfaces[i]), instanceCount - 1, "Interfaces")) {return 11;}
        interfacesList[i] = stoul(loadedInterfaces[i]);
    }

    derivedInterfacesList = new DerivedInterfaceIds*[derivedInterfacesCount];
    derivedInterfacesLengths = new uint32_t[derivedInterfacesCount]; // lengths of all derived interfaces tables
    DerivedInterfaceIds* derivedInterface;
    for (size_t i = 0; i < derivedInterfacesCount; ++i) {
        if (!validateDerivedInterfaceHasValues(loadedDerivedInterfaces[i])) {return 10;}
        derivedInterfacesLengths[i] = loadedDerivedInterfaces[i].size();
        derivedInterface = new DerivedInterfaceIds[derivedInterfacesLengths[i]];
        for (size_t j = 0; j < derivedInterfacesLengths[i]; ++j) {
            if (!validateIdExist(stoul(loadedDerivedInterfaces[i][j][0]), interfacesCount - 1, "Derived interfaces")) {return 11;}
            struct DerivedInterfaceIds derivedInterfaceIds = {stoul(loadedDerivedInterfaces[i][j][0]), stoul(loadedDerivedInterfaces[i][j][1])};
            derivedInterface[j] = derivedInterfaceIds;
        }
        derivedInterfacesList[i] = derivedInterface;
    }

    if (!validateValueDoesNotEqualZero(stoul(loadedClockPeriod), "Clock period")) {return 12;}
    if (!validateValueDoesNotEqualZero(stoul(loadedClockDepth), "Clock depth")) {return 12;}
    clockPeriod = stoul(loadedClockPeriod); // time in nanoseconds
    clockDepth = stoul(loadedClockDepth); // number of clock states

    strobeUpInstanceList = new uint32_t[instanceCount]; // strobe up order (instance id)
    strobeUpInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe up instance (interfaces id)
    strobeUpClock = new bool* [instanceCount]; // strobe up activation for instances

    strobeDownInstanceList = new uint32_t[instanceCount]; // strobe down order (instance id)
    strobeDownInterfacesList = new uint32_t[instanceCount]; // interfaces given for every strobe down instance (interfaces id)
    strobeDownClock = new bool* [instanceCount]; // strobe down activation for instances

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
        if (!validateVectorSize(loadedStrobeUpClock[i], clockDepth, "Strobe up clock")) {return 8;}
        if (!validateVectorSize(loadedStrobeDownClock[i], clockDepth, "Strobe down clock")) {return 8;}
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
    return 0;
}

void loadConfig(){
    loadDataFromFile();
    processRawData();
}
