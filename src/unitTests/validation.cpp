#include "../../boost/boost/test/unit_test.hpp"
#include "../validation.hpp"

using namespace std;

streambuf* buffer = cout.rdbuf();

BOOST_AUTO_TEST_SUITE( testValidation )
     
    BOOST_AUTO_TEST_SUITE( testStringIsInteger )
   
        BOOST_AUTO_TEST_CASE( testStringIsInteger_emptyString ) {
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST( !validateStringIsInteger("", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"\" is not an integer (\"test\" section of config.txt).\n" );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_singleDigit ) {
            BOOST_TEST( validateStringIsInteger("2", "test") );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_multiDigit ) {
            BOOST_TEST( validateStringIsInteger("242", "test") );
        }
    
        BOOST_AUTO_TEST_CASE( testStringIsInteger_everyDigit ) {
            BOOST_TEST( validateStringIsInteger("1234567890", "test") );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_zeroFirst ) {
            BOOST_TEST( validateStringIsInteger("02", "test") );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_alphabetic ) {
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST( !validateStringIsInteger("Test", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"Test\" is not an integer (\"test\" section of config.txt).\n" );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_alphanumericNumberFirst ) {
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST( !validateStringIsInteger("1Test", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"1Test\" is not an integer (\"test\" section of config.txt).\n" );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_alphanumericNumberLast ) {
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST( !validateStringIsInteger("Test1", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"Test1\" is not an integer (\"test\" section of config.txt).\n" );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_alphanumericZeroInside ) {
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST( !validateStringIsInteger("Tes1t", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"Tes1t\" is not an integer (\"test\" section of config.txt).\n" );
        }

        BOOST_AUTO_TEST_CASE( testStringIsInteger_space ) {
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST( !validateStringIsInteger(" ", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \" \" is not an integer (\"test\" section of config.txt).\n" );
        }

    BOOST_AUTO_TEST_SUITE_END()
        
    BOOST_AUTO_TEST_SUITE( testStringIsBool )
    
        BOOST_AUTO_TEST_CASE ( testStringIsBool_true ){
            BOOST_TEST ( validateStringIsBool("true", "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_True ){
            BOOST_TEST ( validateStringIsBool("True", "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_TRUE ){
            BOOST_TEST ( validateStringIsBool("TRUE", "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_false ){
            BOOST_TEST ( validateStringIsBool("false", "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_False ){
            BOOST_TEST ( validateStringIsBool("False", "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_FALSE ){
            BOOST_TEST ( validateStringIsBool("FALSE", "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_helloWorld ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateStringIsBool("Hello World!", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"Hello World!\" is not a boolean value (\"test\" section of config.txt).\n" );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_tabulator ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateStringIsBool("\t", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"\t\" is not a boolean value (\"test\" section of config.txt).\n" );
        }
        
        BOOST_AUTO_TEST_CASE ( testStringIsBool_emptyString ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateStringIsBool("", "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Value \"\" is not a boolean value (\"test\" section of config.txt).\n" );
        }

    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testVectorSize )
    
        BOOST_AUTO_TEST_CASE ( testVectorSize_empty_goodValue ){
            vector<string> test;
            BOOST_TEST ( validateVectorSize(test, 0, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorSize_empty_badValue ){
            stringstream string_buffer;
            vector<string> test = {};
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateVectorSize(test, 6, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Invalid number of values - \"\" - expected 6 values (\"test\" section of config.txt).\n" );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorSize_singleElement_goodValue ){
            vector<string> test = {"test"};
            BOOST_TEST ( validateVectorSize(test, 1, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorSize_singleElement_lowerValue ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<string> test = {"test"};
            BOOST_TEST ( !validateVectorSize(test, 0, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Invalid number of values - \"test\" - expected 0 values (\"test\" section of config.txt).\n" );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorSize_singleElement_higherValue ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<string> test = {"test"};
            BOOST_TEST ( !validateVectorSize(test, 5, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Invalid number of values - \"test\" - expected 5 values (\"test\" section of config.txt).\n" );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorSize_multiElement_goodValue ){
            vector<string> test = {"test", "test", "test"};
            BOOST_TEST ( validateVectorSize(test, 3, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorSize_multiElement_lowerValue ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<string> test = {"test", "test", "test"};
            BOOST_TEST ( !validateVectorSize(test, 0, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Invalid number of values - \"test test test\" - expected 0 values (\"test\" section of config.txt).\n" );
        }

        BOOST_AUTO_TEST_CASE ( testVectorSize_multiElement_higherValue ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<string> test = {"test", "test", "test"};
            BOOST_TEST ( !validateVectorSize(test, 5, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Invalid number of values - \"test test test\" - expected 5 values (\"test\" section of config.txt).\n" );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testDerivedInterfaceCreated )
    
        BOOST_AUTO_TEST_CASE ( testDerivedInterfacesCreated_properTable ){
            vector<vector<vector<string>>> test = {{{"", ""}, {"", ""}}, {{"", ""}, {"", ""}}};
            BOOST_TEST ( validateDerivedInterfaceCreated(test) );
        }
        
        BOOST_AUTO_TEST_CASE ( testDerivedInterfacesCreated_emptyTable ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<vector<vector<string>>> test = {};
            BOOST_TEST ( !validateDerivedInterfaceCreated(test) );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: New derived interface has not been created, but its values were specified (\"Derived interfaces\" section of config.txt).\n" );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testDerivedInterfaceHasValues )
    
        BOOST_AUTO_TEST_CASE ( testDerivedInterfaceHasValues_properTable ){
            vector<vector<string>> test = {{"", ""}, {"", ""}};
            BOOST_TEST ( validateDerivedInterfaceHasValues(test) );
        }
        
        BOOST_AUTO_TEST_CASE ( testDerivedInterfaceHasValues_emptyTable ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<vector<string>> test = {};
            BOOST_TEST ( !validateDerivedInterfaceHasValues(test) );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: New derived interface has been created, but its values were not specified (\"Derived interfaces\" section of config.txt).\n" );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testIdExist )
    
        BOOST_AUTO_TEST_CASE ( testIdExist_lowerThanMax ){
            BOOST_TEST ( validateIdExist(3, 5, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testIdExist_exualToMax ){
            BOOST_TEST ( validateIdExist(5, 5, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testIdExist_greaterThanMax ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateIdExist(10, 5, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Specified ID \"10\" does not exist (\"test\" section of config.txt).\n" );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
        
    BOOST_AUTO_TEST_SUITE( testValueDoesNotEqualZero )
    
        BOOST_AUTO_TEST_CASE ( testValueDoesNotEqualZero_notEqualToZero ){
            BOOST_TEST ( validateValueDoesNotEqualZero(5, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testValueDoesNotEqualZero_equalToZero ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateValueDoesNotEqualZero(0, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Specified value equals zero (\"test\" section of config.txt).\n" );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testValueEqualsNumberOfInstances )
    
        BOOST_AUTO_TEST_CASE ( testValueEqualsNumberOfInstances_equal ){
            BOOST_TEST ( validateValueEqualsNumberOfInstances(5, 5, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testValueEqualsNumberOfInstances_notEqual ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            BOOST_TEST ( !validateValueEqualsNumberOfInstances(5, 1, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Number of values in section does not equal number of instances (\"test\" section of config.txt).\n" );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testVectorHasUniqueValues )
    
        BOOST_AUTO_TEST_CASE ( testVectorHasUniqueValues_emptyVector ){
            vector<string> test = {};
            BOOST_TEST ( validateVectorHasUniqueValues(test, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorHasUniqueValues_singleElement ){
            vector<string> test = {"test"};
            BOOST_TEST ( validateVectorHasUniqueValues(test, "test") );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorHasUniqueValues_doubleElement_equal ){
            stringstream string_buffer;
            cout.rdbuf(string_buffer.rdbuf());
            vector<string> test = {"test", "test"};
            BOOST_TEST ( !validateVectorHasUniqueValues(test, "test") );
            cout.rdbuf(buffer);
            string output = string_buffer.str();
            BOOST_TEST( output == "ERROR: Values in section are not unique (\"test\" section of config.txt).\n" );
        }
        
        BOOST_AUTO_TEST_CASE ( testVectorHasUniqueValues_doubleElement_unique ){
            vector<string> test = {"testA", "testB"};
            BOOST_TEST ( validateVectorHasUniqueValues(test, "test") );
        }
        
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
