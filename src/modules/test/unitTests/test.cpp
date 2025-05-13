#define BOOST_TEST_MODULE testTestDll
#include <boost/test/unit_test.hpp>

extern "C" {
    #include "..\testDll.h"
}

BOOST_AUTO_TEST_SUITE( testTestDll )
    BOOST_AUTO_TEST_SUITE( testCreate )

        BOOST_AUTO_TEST_CASE ( testCreate_isInstanceCreated ){
            void* instance = NULL;
            enum Error error;
        
            error = create(&instance, NULL);
        
            BOOST_TEST ( !error );
            BOOST_TEST ( instance );
        }
        
        BOOST_AUTO_TEST_CASE ( testCreate_validateInstance ){
            struct Instance* instance;
            enum Error error;
        
            error = create((void**) &instance, NULL);
        
            BOOST_TEST ( !error );
            BOOST_TEST ( !instance->value );
            BOOST_TEST ( instance->character );
            BOOST_TEST ( !*instance->character );
        }
        
        BOOST_AUTO_TEST_CASE ( testCreate_instancePararameters ){
            struct Instance* instance;
            uint8_t parameters[2] = {5, 10};
            enum Error error;
        
            error = create((void**) &instance, parameters);
        
            BOOST_TEST ( !error );
            BOOST_TEST ( instance->value == 5 );
            BOOST_TEST ( instance->character );
            BOOST_TEST ( *instance->character == 10 );
        }
        
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testCreateInterfaces )

        BOOST_AUTO_TEST_CASE ( testCreateInterfaces_areInterfacesCreated){
            struct Instance instance = {};
            void ** interfaces = NULL;
            uint16_t count = 0;
            enum Error error;
        
            error = createInterfaces(&instance, &interfaces, &count);
        
            BOOST_TEST ( !error );
            BOOST_TEST ( interfaces );
            BOOST_TEST ( *interfaces );
            BOOST_TEST ( count == 1 );
        }
        
        BOOST_AUTO_TEST_CASE ( testCreateInterfaces_validateInterfaces ){
            struct Instance instance = {};
            uint8_t ** interfaces = NULL;
            uint16_t count = 0;
            enum Error error;
        
            error = createInterfaces(&instance, (void***) &interfaces, &count);
        
            BOOST_TEST ( !error );
            BOOST_TEST ( interfaces );
            BOOST_TEST ( *interfaces );
            BOOST_TEST ( **interfaces == 0 );
            BOOST_TEST ( count == 1 );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testStrobeUp )

        BOOST_AUTO_TEST_CASE ( testStrobeUp_badInstanceDetection ){
            enum Error error;
        
            error = strobeUp(NULL, NULL);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
        
        BOOST_AUTO_TEST_CASE ( testStrobeUp_badInterfacesDetection ){
            struct Instance instance = {};
            enum Error error;
        
            error = strobeUp(&instance, NULL);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testStrobeDown )
    
        BOOST_AUTO_TEST_CASE ( testStrobeDown_badInstanceDetection ){
            enum Error error;
        
            error = strobeDown(NULL, NULL);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
        
        BOOST_AUTO_TEST_CASE ( testStrobeDown_badInterfacesDetection ){
            struct Instance instance = {};
            enum Error error;
        
            error = strobeDown(&instance, NULL);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
        
        BOOST_AUTO_TEST_CASE ( testStrobeDown_InstanceAlteration ){
            struct Instance instance = {};
            uint8_t interface_0 = 5;
            uint8_t* interfaces = &interface_0;
            enum Error error;
        
            error = strobeDown(&instance, (void**) &interfaces);
        
            BOOST_TEST ( !error );
            BOOST_TEST ( instance.value == 5 );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( testDestroy )
        
        BOOST_AUTO_TEST_CASE ( testDestroy_BadInstanceDetection ){
            enum Error error;
        
            error = destroy(NULL);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
        
        BOOST_AUTO_TEST_CASE ( testDestroy_GarbageCollection ){
            struct Instance instance = {};
            char character = 10;
            instance.value = 5;
            instance.character = &character;
        
            destroyGarbageCollect(&instance);
        
            BOOST_TEST ( character == 0 );
            BOOST_TEST ( instance.value == 0 );
        }
        
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE( testDestroyInterfaces )
        
        BOOST_AUTO_TEST_CASE ( testDestroyInterfaces_badInstanceDetection ){
            uint8_t interface_0 = 0;
            uint8_t* interfaces = &interface_0;
            enum Error error;
        
            error = destroyInterfaces(NULL, (void**) &interfaces, 1);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
    
        BOOST_AUTO_TEST_CASE ( testDestroyInterfaces_badInterfacesDetection ){
            struct Instance instance = {};
            enum Error error;
        
            error = destroyInterfaces(&instance, NULL, 1);
        
            BOOST_TEST ( error == BAD_ARGUMENT );
        }
        
        BOOST_AUTO_TEST_CASE ( testDestroyInterfaces_garbageCollection ){
            uint8_t interface_0 = 5;
            uint8_t* interfaces = &interface_0;
        
            destroyInterfacesGarbageCollect((void**) &interfaces);
        
            BOOST_TEST ( interface_0 == 0 );
        }

    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
