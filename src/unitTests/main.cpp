extern "C" {
    #include "../unitTestSystem/unitTest.h"
}
#include "../misc.hpp"

using namespace std;

#define LENGTH 11

bool testCompareStringVectorsEqual() {
    vector<string> vec1 = {"Hello", "World!"};
    vector<string> vec2 = {"Hello", "World!"};
    return compareStringVectors(result, expectedResult);
}

bool testCompareStringVectorsDifferent() {
    vector<string> vec1 = {"Hello", "World!"};
    vector<string> vec2 = {"World!", "Hello"};
    return !compareStringVectors(result, expectedResult);
}

bool testSplitString1(){
    string str = "Hello World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString2(){
    string str = "1, 2, 3, 4, 5";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"1", "2", "3", "4", "5"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString3(){
    string str = " Hello World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"", "Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString4(){
    string str = "Hello World! ";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!", ""};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString5(){
    string str = "Hello  World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString6(){
    string str = "Hello    World!";
    string delimiter = "  ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString7(){
    string str = "Hello     World!";
    string delimiter = "  ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", " World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString8(){
    string str = " Hello, World!";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {" Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString9(){
    string str = "Hello, World!,";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!,"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

extern "C" struct UnitTestModuleResult testMain();

struct UnitTestModuleResult testMain()
{
    struct UnitTestModuleResult result;
    result.tests = LENGTH;
    
    bool (*funcs[LENGTH])() = {
        testCompareStringVectorsEqual,
        testCompareStringVectorsDifferent,
        testSplitString1,
        testSplitString2,
        testSplitString3,
        testSplitString4,
        testSplitString5,
        testSplitString6,
        testSplitString7,
        testSplitString8,
        testSplitString9,
    };
    
    string names[LENGTH] = {
        "testCompareStringVectorsEqual",
        "testCompareStringVectorsDifferent",
        "testSplitString1",
        "testSplitString2",
        "testSplitString3",
        "testSplitString4",
        "testSplitString5",
        "testSplitString6",
        "testSplitString7",
        "testSplitString8",
        "testSplitString9",
    };

    char* namesChar[LENGTH];

    for (uint16_t i = 0; i < LENGTH; i++){
        namesChar[i] = new char[names[i].length() + 1];
        namesChar[i] = strcpy(namesChar[i], names[i].c_str());
    }

    result.fails = iterateTests(namesChar, funcs, LENGTH);
    return result;
}
