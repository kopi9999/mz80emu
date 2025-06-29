#include "main.hpp"
#include "config.hpp"
#include "init.hpp"
#include "misc.hpp"
#include <chrono>
#include <iostream>

extern "C" {
    #include "loadlib.h"
}

using namespace std;

struct Modules modules = {};

void** instances;
void*** interfaces;

struct InstanceInfo instanceInfo = {};
struct InterfacesInfo interfacesInfo = {};
struct ClockInfo clockInfo = {};

int main()
{
    enum CrashCode crash;
    crash = loadConfig(&modules, &instanceInfo, &interfacesInfo, &clockInfo);
    if (crash) {return crash;}
    
    crash = init(&modules, &instances, &interfaces, instanceInfo, interfacesInfo);
    if (crash) {return crash;}

    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::nanoseconds duration = chrono::nanoseconds(clockInfo.period);
    uint16_t tmpModuleId;
    Error error;
    uint32_t clockState = 0;

    while (true){
        start = chrono::high_resolution_clock::now();
        end = start + duration;

        for (uint32_t i = 0; i < instanceInfo.count; i++){
            if (clockInfo.strobeUpClock[i][clockState]){
                tmpModuleId = instanceInfo.list[clockInfo.strobeUpInstanceList[i]];
                error = modules.strobeUpFuncs[tmpModuleId](instances[clockInfo.strobeUpInstanceList[i]], (void**) &interfaces[clockInfo.strobeUpInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe up error " << error << ".\n"; break;}
            }
        }
        
        for (uint32_t i = 0; i < instanceInfo.count; i++){
            if (clockInfo.strobeDownClock[i][clockState]){
                tmpModuleId = instanceInfo.list[clockInfo.strobeDownInstanceList[i]];
                error = modules.strobeDownFuncs[tmpModuleId](instances[clockInfo.strobeDownInstanceList[i]], (void**) &interfaces[clockInfo.strobeDownInterfacesList[i]]);
                if (error) {cout << "ERROR [" << modules.names[tmpModuleId] << "]: strobe down error " << error << ".\n"; break;}
            }
        }
        
        do {
        start = chrono::high_resolution_clock::now();
        } while (end > start);

        ++clockState;
        if (clockState == clockInfo.depth) {clockState = 0;}

    }

    unloadLibs(modules.pointers, modules.count);
    return convertErrorToCrash(error);
}

//test jocha
