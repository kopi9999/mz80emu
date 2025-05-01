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

struct InterfacesInfo interfacesInfo = {};
struct ClockInfo clockInfo = {};

int main()
{
    loadConfig(&interfacesInfo, &clockInfo);
    init(interfacesInfo);

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::nanoseconds duration = chrono::nanoseconds(clockInfo.clockPeriod);
    uint16_t tmpModuleId;
    Error error;
    uint32_t clockState = 0;

    while (true){
        start = chrono::high_resolution_clock::now();
        end = start + duration;

        for (uint32_t i = 0; i < instanceCount; i++){
            if (clockInfo.strobeUpClock[i][clockState]){
                tmpModuleId = instancesList[clockInfo.strobeUpInstanceList[i]];
                error = modules.strobeUpFuncs[tmpModuleId](instances[clockInfo.strobeUpInstanceList[i]], (void**) &interfaces[clockInfo.strobeUpInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe up error " << error << ".\n"; break;}
            }
        }
        
        for (uint32_t i = 0; i < instanceCount; i++){
            if (clockInfo.strobeDownClock[i][clockState]){
                tmpModuleId = instancesList[clockInfo.strobeDownInstanceList[i]];
                error = modules.strobeDownFuncs[tmpModuleId](instances[clockInfo.strobeDownInstanceList[i]], (void**) &interfaces[clockInfo.strobeDownInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe down error " << error << ".\n"; break;}
            }
        }
        
        do {
        start = chrono::high_resolution_clock::now();
        } while (end > start);

        ++clockState;
        if (clockState == clockInfo.clockDepth) {clockState = 0;}

    }

    unloadLibs(modules.pointers, modules.count);
    return 0;
}

//test jocha
