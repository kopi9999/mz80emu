extern "C" {
    #include "../unitTestSystem/unitTest.h"
}
#include "../misc.hpp"

using namespace std;

#define LENGTH 11

bool testCompareStringVectors_equal() {
    vector<string> vec1 = {"Hello", "World!"};
    vector<string> vec2 = {"Hello", "World!"};
    return compareStringVectors(vec1, vec2);
}

bool testCompareStringVectors_different() {
    vector<string> vec1 = {"Hello", "World!"};
    vector<string> vec2 = {"World!", "Hello"};
    return !compareStringVectors(vec1, vec2);
}

bool testSplitString_oneCharDelimiter(){
    string str = "Hello World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_twoCharsDelimiter(){
    string str = "1, 2, 3, 4, 5";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"1", "2", "3", "4", "5"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_delimiterOnStart(){
    string str = " Hello World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"", "Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_delimiterOnEnd(){
    string str = "Hello World! ";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!", ""};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_oneCharTwoDelimitersInARow(){
    string str = "Hello  World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_twoCharsTwoDelimitersInARow(){
    string str = "Hello    World!";
    string delimiter = "  ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_twoAndHalfDelimiterInARow(){
    string str = "Hello     World!";
    string delimiter = "  ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", " World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_halfDelimiterOnStart(){
    string str = " Hello, World!";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {" Hello", "World!"};
    if (!compareStringVectors(result, expectedResult)) {return false;}
    return true;
}

bool testSplitString_halfDelimiterOnEnd(){
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
        testCompareStringVectors_equal,
        testCompareStringVectors_different,
        testSplitString_oneCharDelimiter,
        testSplitString_twoCharsDelimiter,
        testSplitString_delimiterOnStart,
        testSplitString_delimiterOnEnd,
        testSplitString_oneCharTwoDelimitersInARow,
        testSplitString_twoCharsTwoDelimitersInARow,
        testSplitString_twoAndHalfDelimiterInARow,
        testSplitString_halfDelimiterOnStart,
        testSplitString_halfDelimiterOnEnd,
    };
    
    string names[LENGTH] = {
        "testCompareStringVectors_equal",
        "testCompareStringVectors_different",
        "testSplitString_oneCharDelimiter",
        "testSplitString_twoCharsDelimiter",
        "testSplitString_delimiterOnStart",
        "testSplitString_delimiterOnEnd",
        "testSplitString_oneCharTwoDelimitersInARow",
        "testSplitString_twoCharsTwoDelimitersInARow",
        "testSplitString_twoAndHalfDelimiterInARow",
        "testSplitString_halfDelimiterOnStart",
        "testSplitString_halfDelimiterOnEnd",
    };

    char* namesChar[LENGTH];

    for (uint16_t i = 0; i < LENGTH; i++){
        namesChar[i] = new char[names[i].length() + 1];
        namesChar[i] = strcpy(namesChar[i], names[i].c_str());
    }

    result.fails = iterateTests(namesChar, funcs, LENGTH);
    return result;
}
