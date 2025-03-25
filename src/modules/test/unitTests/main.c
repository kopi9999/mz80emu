#include "../testdll.h"
#include <stdbool.h>

#define LENGTH 3

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

void iterateTests(char* names[], bool (*funcs[])(), uint16_t length)
{
    uint16_t fails = 0;
    for (size_t i = 0; i < length; ++i){
        printf("%s: ", names[i]);
        if (funcs[i]()){
            printf("PASS\n");
            continue;
        }
        ++fails;
        printf("FAIL\n");
    }
    printf("\n%u tests ran, %u failed", length, fails);
}

int main()
{
    bool (*funcs[LENGTH])() = {testIfInstanceIsCreated, testIfCreatedInstanceIsValid, testInstanceCreationPararameters};
    char* names[LENGTH] = {"testIfInstanceIsCreated", "testIfCreatedInstanceIsValid", "testInstanceCreationPararameters"};
    iterateTests(names, funcs, LENGTH);
    return 0;
}
