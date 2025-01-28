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

    if (loadLibs(libs, libNames, libCount))
    {
        unloadLibs(libs, libCount);
        exit(1);

    }
    
    //void** createFuncs = new void*[libCount];
    //loadFuncs(createFuncs, libs, libCount, "create")

    unloadLibs(libs, libCount);
    return 0;
}

//test jocha
