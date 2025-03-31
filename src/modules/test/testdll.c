#include "testdll.h"

enum Error create(void** instance, void*__restrict parameters)
{
    struct Instance* instanceTmp = calloc(1, sizeof(struct Instance));
    if(!instanceTmp) {return MALLOC_ERROR;}
    
    instanceTmp->character = calloc(1, sizeof(char));
    if(!instanceTmp->character) {return MALLOC_ERROR;}

    if(parameters){
        uint8_t* ptmp = (uint8_t*) parameters;
        instanceTmp->value = ptmp[0]; 
        *(instanceTmp->character) = ptmp[1];
    } else{
        instanceTmp->value = 0;
        *(instanceTmp->character) = 0;
    }

    *instance = instanceTmp;
    return SUCCESS;
}


enum Error createInterfaces(void*__restrict instance, void*** interfaces, uint16_t*__restrict count)
{
    *count = 1;

    *interfaces = calloc(1, sizeof(void*));
    if (!*interfaces) {return MALLOC_ERROR;}

    *interfaces[0] = calloc(1, sizeof(uint8_t));
    if (!(*interfaces)[0]) {return MALLOC_ERROR;}
    
    *count = 1;
    return SUCCESS;
}

enum Error strobeUp(void*__restrict instance, void**__restrict interfaces)
{
    if(!instance || !interfaces) {return BAD_ARGUMENT;}
    if(!interfaces[0]) {return BAD_ARGUMENT;}
    
    struct Instance* instanceTmp = (struct Instance*) instance;
    printf("%d\n", instanceTmp->value);
    *(uint8_t*) interfaces[0] = rand();

    return SUCCESS;
}

enum Error strobeDown(void*__restrict instance, void**__restrict interfaces)
{
    if(!instance || !interfaces) {return BAD_ARGUMENT;}
    if(!interfaces[0]) {return BAD_ARGUMENT;}

    struct Instance* instanceTmp = (struct Instance*) instance;
    instanceTmp->value = *(uint8_t*)interfaces[0];

    return SUCCESS;
}

void destroyGarbageCollect(struct Instance* instance)
{
    *instance->character = 0;
    instance->character = NULL;
    instance->value = 0;
}

enum Error destroy(void* instance)
{
    if(!instance){return BAD_ARGUMENT;}

    struct Instance* instanceTmp = instance;
    destroyGarbageCollect(instanceTmp);
    free(instanceTmp->character);
    free(instanceTmp);

    return SUCCESS;
}

void destroyInterfacesGarbageCollect(void** interfaces)
{
    * (uint8_t*) interfaces[0] = 0;
}

enum Error destroyInterfaces(void*__restrict instance, void** interfaces, uint16_t count)
{
    if (!instance) {return BAD_ARGUMENT;}
    if (!interfaces) {return BAD_ARGUMENT;}
    destroyInterfacesGarbageCollect(interfaces);
    free(interfaces[0]);
    interfaces[0] = NULL;
    free(interfaces);
    return SUCCESS;
}
