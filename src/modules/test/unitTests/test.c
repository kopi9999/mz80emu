#include "../testdll.h"
#include "../../../unitTestSystem/unitTest.h"

#define LENGTH 10

bool testIfInstanceIsCreated(){
    void* instance = NULL;
    enum Error error;

    error = create(&instance, NULL);

    if (error) {return false;}
    if (!instance) {return false;}
    return true;
}

bool testIfCreatedInstanceIsValid(){
    struct Instance* instance;
    enum Error error;

    error = create((void*) &instance, NULL);

    if (error) {return false;}
    if (instance->value){return false;}
    if (!instance->character){return false;}
    if (*instance->character){return false;}
    return true;
}

bool testInstanceCreationPararameters(){
    struct Instance* instance;
    uint8_t parameters[2] = {5, 10};
    enum Error error;

    error = create((void*) &instance, parameters);

    if (error) {return false;}
    if (instance->value != 5){return false;}
    if (!instance->character){return false;}
    if (*instance->character != 10){return false;}
    return true;
}

bool testIfInterfacesAreCreated(){
    struct Instance instance = {};
    void ** interfaces = NULL;
    uint16_t count = 0;
    enum Error error;

    error = createInterfaces(&instance, &interfaces, &count);

    if (error) {return false;}
    if (!interfaces) {return false;}
    if (!*interfaces) {return false;}
    if (count != 1) {return false;}
    return true;
}

bool testIfCreatedInterfacesAreValid(){
    struct Instance instance = {};
    uint8_t ** interfaces = NULL;
    uint16_t count = 0;
    enum Error error;

    error = createInterfaces(&instance, (void***) &interfaces, &count);

    if (error) {return false;}
    if (!interfaces) {return false;}
    if (!*interfaces) {return false;}
    if (**interfaces != 0) {return false;}
    if (count != 1) {return false;}
    return true;
}

bool testStrobeUpBadInstanceDetection(){
    enum Error error;

    error = strobeUp(NULL, NULL);

    if (error == BAD_ARGUMENT) {return true;}
    return false;
}

bool testStrobeUpBadInterfacesDetection(){
    struct Instance instance = {};
    enum Error error;

    error = strobeUp(&instance, NULL);

    if (error == BAD_ARGUMENT) {return true;}
    return false;
}

bool testStrobeDownBadInstanceDetection(){
    enum Error error;

    error = strobeDown(NULL, NULL);

    if (error == BAD_ARGUMENT) {return true;}
    return false;
}

bool testStrobeDownBadInterfacesDetection(){
    struct Instance instance = {};
    enum Error error;

    error = strobeDown(&instance, NULL);

    if (error == BAD_ARGUMENT) {return true;}
    return false;
}

bool testStrobeDownInstanceAlteration(){
    struct Instance instance = {};
    uint8_t interface_1 = 5;
    uint8_t* interfaces = &interface_1;
    enum Error error;

    error = strobeDown(&instance, (void**) &interfaces);

    if (error) {return false;}
    if (instance.value != 5) {return false;}
    return true;
}

struct UnitTestModResult testTestDll()
{
    struct UnitTestModResult result;
    result.tests = LENGTH;
    
    bool (*funcs[LENGTH])() = {
        testIfInstanceIsCreated,
        testIfCreatedInstanceIsValid,
        testInstanceCreationPararameters, 
        testIfInterfacesAreCreated,
        testIfCreatedInterfacesAreValid,
        testStrobeUpBadInstanceDetection,
        testStrobeUpBadInterfacesDetection,
        testStrobeDownBadInstanceDetection,
        testStrobeDownBadInterfacesDetection,
        testStrobeDownInstanceAlteration
    };
    
    char* names[LENGTH] = {
        "testIfInstanceIsCreated", 
        "testIfCreatedInstanceIsValid", 
        "testInstanceCreationPararameters", 
        "testIfInterfacesAreCreated", 
        "testIfCreatedInterfacesAreValid", 
        "testStrobeUpBadInstanceDetection", 
        "testStrobeUpBadInterfacesDetection", 
        "testStrobeDownBadInstanceDetection", 
        "testStrobeDownBadInterfacesDetection", 
        "testStrobeDownInstanceAlteration"
    };
    result.fails = iterateTests(names, funcs, LENGTH);
    return result;
}
