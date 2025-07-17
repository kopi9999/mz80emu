#define BOOST_TEST_MODULE header-only testModuleFunctions
#include <boost/test/included/unit_test.hpp>

extern "C" {
    #include "moduleInternal.h"
}

const char* moduleName = "";
const char* moduleDescription = "";

using namespace std;


BOOST_AUTO_TEST_SUITE( testModuleFunctions )

    BOOST_AUTO_TEST_SUITE ( testGetName )

        BOOST_AUTO_TEST_CASE( testGetName_noOutput )
        {
            moduleName = "test";
            
            Error error = getName(NULL, 10);
            
            BOOST_TEST ( error == BAD_ARGUMENT );
        } 

        BOOST_AUTO_TEST_CASE( testGetName_moduleNameEmpty )
        {
            moduleName = "";
            char output[10] = "";
            
            Error error = getName(output, 10);
            
            BOOST_TEST ( error == SUCCESS );
            BOOST_TEST ( !strcmp(moduleName, output) );
        } 

        BOOST_AUTO_TEST_CASE( testGetName_outputLongerThanInput )
        {
            moduleName = "test";
            char output[10] = "";
            
            Error error = getName(output, 10);
            
            BOOST_TEST ( error == SUCCESS );
            BOOST_TEST ( !strcmp(moduleName, output) );
        } 

        BOOST_AUTO_TEST_CASE( testGetName_outputShorterThanInput )
        {
            moduleName = "testtest";
            char output[5] = "";
            
            Error error = getName(output, 5);
            
            BOOST_TEST ( error == SIZE_MISMATCH );
        } 

        BOOST_AUTO_TEST_CASE( testGetName_outputIdenticalToInput )
        {
            moduleName = "test";
            char output[5] = "";
            
            Error error = getName(output, 5);
            
            BOOST_TEST ( error == SUCCESS );
            BOOST_TEST ( !strcmp(moduleName, output) );
        } 

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE ( testGetDescription )

        BOOST_AUTO_TEST_CASE( testGetDescription_noOutput )
        {
            moduleDescription = "test";
            
            Error error = getDescription(NULL, 10);
            
            BOOST_TEST ( error == BAD_ARGUMENT );
        } 

        BOOST_AUTO_TEST_CASE( testGetDescription_moduleNameEmpty )
        {
            moduleDescription = "";
            char output[10] = "";
            
            Error error = getDescription(output, 10);
            
            BOOST_TEST ( error == SUCCESS );
            BOOST_TEST ( !strcmp(moduleDescription, output) );
        } 

        BOOST_AUTO_TEST_CASE( testGetDescription_outputLongerThanInput )
        {
            moduleDescription = "test";
            char output[10] = "";
            
            Error error = getDescription(output, 10);
            
            BOOST_TEST ( error == SUCCESS );
            BOOST_TEST ( !strcmp(moduleDescription, output) );
        } 

        BOOST_AUTO_TEST_CASE( testGetDescription_outputShorterThanInput )
        {
            moduleDescription = "testtest";
            char output[5] = "";
            
            Error error = getDescription(output, 5);
            
            BOOST_TEST ( error == SIZE_MISMATCH );
        } 

        BOOST_AUTO_TEST_CASE( testGetDescription_outputIdenticalToInput )
        {
            moduleDescription = "test";
            char output[5] = "";
            
            Error error = getDescription(output, 5);
            
            BOOST_TEST ( error == SUCCESS );
            BOOST_TEST ( !strcmp(moduleDescription, output) );
        } 

    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
