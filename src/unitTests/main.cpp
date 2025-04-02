extern "C" {
    #include "../unitTestSystem/unitTest.h"
}
#include "../misc.hpp"

using namespace std;

#define LENGTH 31


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

bool testCompareStringVectors_emptyVector() {
    vector<string> vec1 = {};
    vector<string> vec2 = {};
    return compareStringVectors(vec1, vec2);
}


bool testSplitString_oneCharDelimiter(){
    string str = "Hello World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_twoCharsDelimiter(){
    string str = "1, 2, 3, 4, 5";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"1", "2", "3", "4", "5"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_delimiterOnStart(){
    string str = " Hello World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"", "Hello", "World!"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_delimiterOnEnd(){
    string str = "Hello World! ";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!", ""};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_oneCharTwoDelimitersInARow(){
    string str = "Hello  World!";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", "World!"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_twoCharsTwoDelimitersInARow(){
    string str = "Hello    World!";
    string delimiter = "  ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", "World!"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_twoAndHalfDelimiterInARow(){
    string str = "Hello     World!";
    string delimiter = "  ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "", " World!"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_halfDelimiterOnStart(){
    string str = " Hello, World!";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {" Hello", "World!"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_halfDelimiterOnEnd(){
    string str = "Hello, World!,";
    string delimiter = ", ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {"Hello", "World!,"};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_emptyString(){
    string str = "";
    string delimiter = " ";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {};
    return compareStringVectors(result, expectedResult);
}

bool testSplitString_emptyDelimiter(){
    string str = "Hello World!";
    string delimiter = "";
    vector<string> result = splitString(str, delimiter);
    vector<string> expectedResult = {};
    return compareStringVectors(result, expectedResult);
}


bool testToLower_lowercase() {
    string str = toLower("hello world!");
    string expectedResult = "hello world!";
    return (str == expectedResult);
}

bool testToLower_uppercase() {
    string str = toLower("HELLO WORLD!");
    string expectedResult = "hello world!";
    return (str == expectedResult);
}

bool testToLower_capitalization() {
    string str = toLower("Hello World!");
    string expectedResult = "hello world!";
    return (str == expectedResult);
}

bool testToLower_emptyString() {
    string str = toLower("");
    string expectedResult = "";
    return (str == expectedResult);
}


bool testStringToBool_true() {
    return stringToBool("true");
}

bool testStringToBool_True() {
    return stringToBool("True");
}

bool testStringToBool_TRUE() {
    return stringToBool("TRUE");
}

bool testStringToBool_false() {
    return !stringToBool("false");
}

bool testStringToBool_helloWorld() {
    return !stringToBool("Hello World!");
}

bool testStringToBool_tabulator() {
    return !stringToBool("\t");
}

bool testStringToBool_emptyString() {
    return !stringToBool("");
}


bool testTrim_spaceOnStart() {
    string str = " HelloWorld!";
    trim(&str);
    string expectedResult = "HelloWorld!";
    return (str == expectedResult);
}

bool testTrim_spaceOnEnd() {
    string str = "HelloWorld! ";
    trim(&str);
    string expectedResult = "HelloWorld!";
    return (str == expectedResult);
}

bool testTrim_variousWhitespaceChars() {
    string str = "\r\t \nHelloWorld! \n\t\r";
    trim(&str);
    string expectedResult = "HelloWorld!";
    return (str == expectedResult);
}

bool testTrim_whitespaceInsideString() {
    string str = "Hello World!";
    trim(&str);
    string expectedResult = "Hello World!";
    return (str == expectedResult);
}

bool testTrim_noWhitespace() {
    string str = "HelloWorld!";
    trim(&str);
    string expectedResult = "HelloWorld!";
    return (str == expectedResult);
}

bool testTrim_emptyString() {
    string str = "";
    trim(&str);
    string expectedResult = "";
    return (str == expectedResult);
}


extern "C" struct UnitTestModuleResult testMain();

struct UnitTestModuleResult testMain()
{
    struct UnitTestModuleResult result;
    result.tests = LENGTH;
    
    bool (*funcs[LENGTH])() = {
        testCompareStringVectors_equal,
        testCompareStringVectors_different,
        testCompareStringVectors_emptyVector,

        testSplitString_oneCharDelimiter,
        testSplitString_twoCharsDelimiter,
        testSplitString_delimiterOnStart,
        testSplitString_delimiterOnEnd,
        testSplitString_oneCharTwoDelimitersInARow,
        testSplitString_twoCharsTwoDelimitersInARow,
        testSplitString_twoAndHalfDelimiterInARow,
        testSplitString_halfDelimiterOnStart,
        testSplitString_halfDelimiterOnEnd,
        testSplitString_emptyString,
        testSplitString_emptyDelimiter,

        testToLower_lowercase,
        testToLower_uppercase,
        testToLower_capitalization,
        testToLower_emptyString,

        testStringToBool_true,
        testStringToBool_True,
        testStringToBool_TRUE,
        testStringToBool_false,
        testStringToBool_helloWorld,
        testStringToBool_tabulator,
        testStringToBool_emptyString,
        
        testTrim_spaceOnStart,
        testTrim_spaceOnEnd,
        testTrim_variousWhitespaceChars,
        testTrim_whitespaceInsideString,
        testTrim_noWhitespace,
        testTrim_emptyString,
    };
    
    string names[LENGTH] = {
        "testCompareStringVectors_equal",
        "testCompareStringVectors_different",
        "testCompareStringVectors_emptyVector",

        "testSplitString_oneCharDelimiter",
        "testSplitString_twoCharsDelimiter",
        "testSplitString_delimiterOnStart",
        "testSplitString_delimiterOnEnd",
        "testSplitString_oneCharTwoDelimitersInARow",
        "testSplitString_twoCharsTwoDelimitersInARow",
        "testSplitString_twoAndHalfDelimiterInARow",
        "testSplitString_halfDelimiterOnStart",
        "testSplitString_halfDelimiterOnEnd",
        "testSplitString_emptyString",
        "testSplitString_emptyDelimiter",

        "testToLower_lowercase",
        "testToLower_uppercase",
        "testToLower_capitalization",
        "testToLower_emptyString",

        "testStringToBool_true",
        "testStringToBool_True",
        "testStringToBool_TRUE",
        "testStringToBool_false",
        "testStringToBool_helloWorld",
        "testStringToBool_tabulator",
        "testStringToBool_emptyString",
        
        "testTrim_spaceOnStart",
        "testTrim_spaceOnEnd",
        "testTrim_variousWhitespaceChars",
        "testTrim_whitespaceInsideString",
        "testTrim_noWhitespace",
        "testTrim_emptyString",
    };

    char* namesChar[LENGTH];

    for (uint16_t i = 0; i < LENGTH; i++){
        namesChar[i] = new char[names[i].length() + 1];
        namesChar[i] = strcpy(namesChar[i], names[i].c_str());
    }

    result.fails = iterateTests(namesChar, funcs, LENGTH);
    return result;
}
