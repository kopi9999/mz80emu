extern "C" {
    #include "../unitTestSystem/unitTest.h"
}
#include "mainFunctions.h"
#include <string>
#include <vector>

using namespace std;

#define LENGTH 1

bool compareStringVectors(vector<string> vec1, vector<string> vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}

bool testSplitString1(){
    string str = "Hello World!";
    string delimiter = " ";
    vector<string> result = {}; //splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
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
