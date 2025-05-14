#define BOOST_TEST_MODULE testMz80emu
#include <boost/test/unit_test.hpp>

#include "../misc.hpp"
extern "C" {
    #include "../misc.c"
}

using namespace std;


BOOST_AUTO_TEST_SUITE( testMisc )

    BOOST_AUTO_TEST_SUITE( testCompareStringVectors )

        BOOST_AUTO_TEST_CASE ( testCompareStringVectors_equal ) {
            vector<string> vec1 = {"Hello", "World!"};
            vector<string> vec2 = {"Hello", "World!"};
            BOOST_TEST ( compareStringVectors(vec1, vec2) );
        }

        BOOST_AUTO_TEST_CASE ( testCompareStringVectors_different ) {
            vector<string> vec1 = {"Hello", "World!"};
            vector<string> vec2 = {"World!", "Hello"};
            BOOST_TEST ( !compareStringVectors(vec1, vec2) );
        }

        BOOST_AUTO_TEST_CASE ( testCompareStringVectors_emptyVector ) {
            vector<string> vec1 = {};
            vector<string> vec2 = {};
            BOOST_TEST ( compareStringVectors(vec1, vec2) );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testSplitString )

        BOOST_AUTO_TEST_CASE ( testSplitString_oneCharDelimiter ){
            string str = "Hello World!";
            string delimiter = " ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_twoCharsDelimiter ){
            string str = "1, 2, 3, 4, 5";
            string delimiter = ", ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"1", "2", "3", "4", "5"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_delimiterOnStart ){
            string str = " Hello World!";
            string delimiter = " ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"", "Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_delimiterOnEnd ){
            string str = "Hello World! ";
            string delimiter = " ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"Hello", "World!", ""};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_oneCharTwoDelimitersInARow ){
            string str = "Hello  World!";
            string delimiter = " ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"Hello", "", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_twoCharsTwoDelimitersInARow ){
            string str = "Hello    World!";
            string delimiter = "  ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"Hello", "", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_twoAndHalfDelimiterInARow ){
            string str = "Hello     World!";
            string delimiter = "  ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"Hello", "", " World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_halfDelimiterOnStart ){
            string str = " Hello, World!";
            string delimiter = ", ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {" Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_halfDelimiterOnEnd ){
            string str = "Hello, World!,";
            string delimiter = ", ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {"Hello", "World!,"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_emptyString ){
            string str = "";
            string delimiter = " ";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitString_emptyDelimiter ){
            string str = "Hello World!";
            string delimiter = "";
            vector<string> result = splitString(str, delimiter);
            vector<string> expectedResult = {};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testSplitByWhitespace )

        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_oneSpace ){
            string str = "Hello World!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_severalSpaces ){
            string str = "Hello   World!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_severalVariousChars ){
            string str = "Hello\r \t\nWorld!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_spaceOnStart ){
            string str = " HelloWorld!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"HelloWorld!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_spaceOnEnd ){
            string str = "HelloWorld! ";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"HelloWorld!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_scatteredSingleChars ){
            string str = "Hello World!\nHello\tWorld! Hello\rWorld!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"Hello", "World!", "Hello", "World!", "Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_scatteredGroupedVariousChars ){
            string str = "Hello \tWorld!\n\rHello \nWorld!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"Hello", "World!", "Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_scatteredGroupedRepeatingChars ){
            string str = "Hello\t\tWorld!\n\nHello  World!\r\rHello  World!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"Hello", "World!", "Hello", "World!", "Hello", "World!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_noWhitespace ){
            string str = "HelloWorld!";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {"HelloWorld!"};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_onlyWhitespace ){
            string str = " \n\r\t";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testSplitByWhitespace_emptyString ){
            string str = "";
            vector<string> result = splitByWhitespace(str);
            vector<string> expectedResult = {};
            BOOST_TEST ( compareStringVectors(result, expectedResult) );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testToLower )

        BOOST_AUTO_TEST_CASE ( testToLower_lowercase ){
            string str = toLower("hello world!");
            string expectedResult = "hello world!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testToLower_uppercase ){
            string str = toLower("HELLO WORLD!");
            string expectedResult = "hello world!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testToLower_capitalization ){
            string str = toLower("Hello World!");
            string expectedResult = "hello world!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testToLower_emptyString ){
            string str = toLower("");
            string expectedResult = "";
            BOOST_TEST ( (str == expectedResult) );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
        
    BOOST_AUTO_TEST_SUITE( testStringToBool )
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_true ){
            BOOST_TEST ( stringToBool("true") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_True ){
            BOOST_TEST ( stringToBool("True") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_TRUE ){
            BOOST_TEST ( stringToBool("TRUE") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_false ){
            BOOST_TEST ( !stringToBool("false") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_helloWorld ){
            BOOST_TEST ( !stringToBool("Hello World!") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_tabulator ){
            BOOST_TEST ( !stringToBool("\t") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringToBool_emptyString ){
            BOOST_TEST ( !stringToBool("") );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
        
    BOOST_AUTO_TEST_SUITE( testTrim )
        
        BOOST_AUTO_TEST_CASE ( testTrim_spaceOnStart ){
            string str = " HelloWorld!";
            trim(&str);
            string expectedResult = "HelloWorld!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrim_spaceOnEnd ){
            string str = "HelloWorld! ";
            trim(&str);
            string expectedResult = "HelloWorld!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrim_variousWhitespaceChars ){
            string str = "\r\t \nHelloWorld! \n\t\r";
            trim(&str);
            string expectedResult = "HelloWorld!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrim_whitespaceInsideString ){
            string str = "Hello World!";
            trim(&str);
            string expectedResult = "Hello World!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrim_noWhitespace ){
            string str = "HelloWorld!";
            trim(&str);
            string expectedResult = "HelloWorld!";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrim_emptyString ){
            string str = "";
            trim(&str);
            string expectedResult = "";
            BOOST_TEST ( (str == expectedResult) );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testTrimLeadingZeros )

        BOOST_AUTO_TEST_CASE ( testTrimLeadingZeros_oneZero ){
            string str = "0123";
            trimLeadingZeros(&str);
            string expectedResult = "123";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrimLeadingZeros_severalZeros ){
            string str = "00000123";
            trimLeadingZeros(&str);
            string expectedResult = "123";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrimLeadingZeros_noZeros ){
            string str = "123";
            trimLeadingZeros(&str);
            string expectedResult = "123";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrimLeadingZeros_zeroOnEnd ){
            string str = "1230";
            trimLeadingZeros(&str);
            string expectedResult = "1230";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrimLeadingZeros_zeroAfterSpace ){
            string str = " 0123";
            trimLeadingZeros(&str);
            string expectedResult = " 0123";
            BOOST_TEST ( (str == expectedResult) );
        }
        
        BOOST_AUTO_TEST_CASE ( testTrimLeadingZeros_emptyString ){
            string str = "";
            trimLeadingZeros(&str);
            string expectedResult = "";
            BOOST_TEST ( (str == expectedResult) );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testConvertErrorToCrash )
    
        BOOST_AUTO_TEST_CASE ( testConvertErrorToCrash_SUUCESS ){
            enum Error test = SUCCESS;
            enum CrashCode output = convertErrorToCrash(test);
            BOOST_TEST ( output == RUNNING );
        }

        BOOST_AUTO_TEST_CASE ( testConvertErrorToCrash_BAD_ARGUMENT ){
            enum Error test = BAD_ARGUMENT;
            enum CrashCode output = convertErrorToCrash(test);
            BOOST_TEST ( output == MODULE_BAD_ARGUMENT );
        }

        BOOST_AUTO_TEST_CASE ( testConvertErrorToCrash_MALLOC_ERROR ){
            enum Error test = MALLOC_ERROR;
            enum CrashCode output = convertErrorToCrash(test);
            BOOST_TEST ( output == MODULE_MALLOC_ERROR );
        }

        BOOST_AUTO_TEST_CASE ( testConvertErrorToCrash_invalid ){
            enum Error test = (enum Error) 34;
            enum CrashCode output = convertErrorToCrash(test);
            BOOST_TEST ( output == MODULE_INVALID_ERROR );
        }

        BOOST_AUTO_TEST_CASE ( testConvertErrorToCrash_NULL ){
            enum Error test = (enum Error) NULL;
            enum CrashCode output = convertErrorToCrash(test);
            BOOST_TEST ( output == RUNNING );
        }

    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testFirstNullPointer )

        BOOST_AUTO_TEST_CASE ( testFirstNullPointer_nullPointerInside ){
            void** test = new void*[5] {(void*) 123, (void*) 456, (void*) 789, NULL, (void*) 321};
            BOOST_TEST ( firstNullPointer(test, 5) == 3 );
            free(test);
        }

        BOOST_AUTO_TEST_CASE ( testFirstNullPointer_firstNullPointer ){
            void** test = new void*[5] {NULL, (void*) 123, (void*) 456, (void*) 789, (void*) 321};
            BOOST_TEST ( firstNullPointer(test, 5) == 0 );
            free(test);
        }

        BOOST_AUTO_TEST_CASE ( testFirstNullPointer_lastNullPointer ){
            void** test = new void*[5] {(void*) 123, (void*) 456, (void*) 789, (void*) 321, NULL};
            BOOST_TEST ( firstNullPointer(test, 5) == 4 );
            free(test);
        }

        BOOST_AUTO_TEST_CASE ( testFirstNullPointer_noNullPointer ){
            void** test = new void*[5] {(void*) 123, (void*) 456, (void*) 789, (void*) 987, (void*) 321};
            BOOST_TEST ( firstNullPointer(test, 5) == 5 );
            free(test);
        }

        BOOST_AUTO_TEST_CASE ( testFirstNullPointer_arrayNullr ){
            void** test = NULL;
            BOOST_TEST ( firstNullPointer(test, 0) == 0 );
            free(test);
        }

    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
