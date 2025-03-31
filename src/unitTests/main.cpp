extern "C" {
    #include "../unitTestSystem/unitTest.h"
}
#include "mainFunctions.h"
#include <string>
#include <vector>

using namespace std;

#define LENGTH 1

bool testSplitString1(){
    string str = "Hello World!";
    string delimeter = " ";
    vector<string> result = {"Hello", "World!"};
    if (splitString(str, delimeter) != result) {return false;}
    return true;
}

extern "C" struct UnitTestModuleResult testMain();

struct UnitTestModuleResult testMain()
{
    struct UnitTestModuleResult result;
    result.tests = LENGTH;
    
    bool (*funcs[LENGTH])() = {
        testSplitString1,
    };
    
    string names[LENGTH] = {
        "testSplitString1",
    };

    char* namesChar[LENGTH];

    for (uint16_t i = 0; i < LENGTH; i++){
        namesChar[i] = new char[names[i].length() + 1];
        namesChar[i] = strcpy(namesChar[i], names[i].c_str());
    }

    result.fails = iterateTests(namesChar, funcs, LENGTH);
    return result;
}
