extern "C" {
    #include "../unitTestSystem/unitTest.h"
}
#include "init.hpp"
#include <string>

using namespace std;

#define LENGTH 1


bool testTest(){
    return true;
}


extern "C" struct UnitTestModuleResult testInit();

struct UnitTestModuleResult testInit()
{
    struct UnitTestModuleResult result;
    result.tests = LENGTH;
    
    bool (*funcs[LENGTH])() = {
        testTest
    };
    
    string names[LENGTH] = {
        "testTest"
    };
    char* namesChar[LENGTH];

    for (uint16_t i = 0; i < LENGTH; i++){
        namesChar[i] = new char[names[i].length() + 1];
        namesChar[i] = strcpy(namesChar[i], names[i].c_str());
    }

    result.fails = iterateTests(namesChar, funcs, LENGTH);
    return result;
}
