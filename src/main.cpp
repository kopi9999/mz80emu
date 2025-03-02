#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

extern "C" {
    #include "loadlib.h"
}

using namespace std;


bool loadLibs(void** libs, vector<string> libNames, uint16_t libCount) //load libraries from std::vector<string>
{
    bool error = false;
    for (uint16_t i = 0; i < libCount; ++i)
    {
        libs[i] = loadLib(libNames[i].c_str());
        if(!libs[i]){
            cout << "ERROR: cannot find library: " << libNames[i] << "\n";
            error = true;
        }
        else 
        {
            cout << "INFO: Loaded library: " << libNames[i] << "\n";
        }
    }
    return error;
}

int main()
{
    //loading from config file

    vector<string> libNames;
    libNames.push_back("test.dll");

    uint16_t libCount = libNames.size(); //number of libraries to load
    void** libs = new void*[libCount];  //table for library pointers

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

    //end of config file
    //loading libraries
    
    if (loadLibs(libs, libNames, libCount))
    {
        unloadLibs(libs, libCount);
        exit(1);

    }
    
    void** createFuncs = new void*[libCount];
    loadFuncs(createFuncs, libs, libCount, "create");

    unloadLibs(libs, libCount);
    return 0;
}

//test jocha
