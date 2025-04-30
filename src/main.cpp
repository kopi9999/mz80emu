#include "main.hpp"
#include "loadConfig.hpp"
#include "init.hpp"
#include <chrono>
#include <iostream>

extern "C" {
    #include "loadlib.h"
}

using namespace std;

struct Modules modules = {};

void** instances;
void*** interfaces;
uint16_t* interfacesElements;

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


int main()
{
    loadConfig();
    init();

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::nanoseconds duration = chrono::nanoseconds(clockPeriod);
    uint16_t tmpModuleId;
    Error error;
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
