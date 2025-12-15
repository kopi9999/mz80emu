#include "memoryMod.h"
#include <stdio.h>

const char* moduleName = "memory";
const char* moduleDescription = "Emulates 64kB of memory";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;
const uint16_t interfacesNumber = 4;
const char* interfacesDescriptions[] = {
    "8 bit data bus", 
    "16 bit address bus", 
    "chip select signal (8 bit as bool)", 
    "read enable signal (8 bit as bool)"
    "write enable signal (8 bit as bool)"
};

enum Error create(void** instance, void*__restrict parameters)
{
    struct Instance* instanceTmp = calloc(1, sizeof(struct Instance));
    instanceTmp->data = calloc(65536, sizeof(uint8_t));
    instanceTmp->size = 65536;

    *instance = (void*) instanceTmp;
    return SUCCESS;
}


enum Error createInterfaces(void*__restrict instance, void*** interfaces, uint16_t*__restrict count)
{ 
    *interfaces = calloc(4, sizeof(void*));
    if (!*interfaces) {return MALLOC_ERROR;}

    (*interfaces)[0] = calloc(1, sizeof(uint8_t)); //data bus
    if (!(*interfaces)[0]) {return MALLOC_ERROR;}
    
    (*interfaces)[1] = calloc(1, sizeof(uint16_t)); //address bus
    if (!(*interfaces)[1]) {return MALLOC_ERROR;}
    
    (*interfaces)[2] = calloc(1, sizeof(uint8_t)); //chip select
    if (!(*interfaces)[2]) {return MALLOC_ERROR;}
    
    (*interfaces)[3] = calloc(1, sizeof(uint8_t)); //read enable
    if (!(*interfaces)[3]) {return MALLOC_ERROR;}
    
    (*interfaces)[4] = calloc(1, sizeof(uint8_t)); //write enable
    if (!(*interfaces)[4]) {return MALLOC_ERROR;}

    *count = 5;
    return SUCCESS;
}

enum Error strobeUp(void*__restrict instance, void**__restrict interfaces)
{
    if (!instance) {return BAD_ARGUMENT;}
    if (!interfaces) {return BAD_ARGUMENT;}
    
    uint8_t data = *(uint8_t*) interfaces[0];
    uint16_t address = *(uint8_t*) interfaces[1];
    uint8_t select = *(uint8_t*) interfaces[2];
    uint8_t read = *(uint8_t*) interfaces[3];
    uint8_t write = *(uint8_t*) interfaces[4];

    struct Instance* instanceTmp = instance;
    
    if (instanceTmp->readState == 0 && read == 1 && select) {instanceTmp->readTrigger = 1;}
    if (instanceTmp->writeState == 0 && write == 1 && select) {
        instanceTmp->data[address] = data;
    }

    instanceTmp->readState = read;
    instanceTmp->writeState = write;
    return SUCCESS;
}

enum Error strobeDown(void*__restrict instance, void**__restrict interfaces)
{
    if (!instance) {return BAD_ARGUMENT;}
    if (!interfaces) {return BAD_ARGUMENT;}
    
    void* interfacesTmp = *interfaces;
    uint8_t* data = ((uint8_t*) interfacesTmp);
    uint16_t* address = ((uint16_t*) interfacesTmp + 1);

    struct Instance* instanceTmp = instance;

    if (instanceTmp->readTrigger) { 
        *data = instanceTmp->data[*address];
        instanceTmp->readState = 0;
        instanceTmp->readTrigger = 0;
    }
    return SUCCESS;
}

enum Error destroy(void* instance)
{
    free(((struct Instance*) instance)->data);
    free(instance);
    return SUCCESS;
}

enum Error destroyInterfaces(void*__restrict instance, void** interfaces, uint16_t count)
{
    if (!instance) {return BAD_ARGUMENT;}
    if (!interfaces) {return BAD_ARGUMENT;}
    free(interfaces[0]);
    free(interfaces[1]);
    free(interfaces[2]);
    free(interfaces[3]);
    free(interfaces[4]);
    free(interfaces);
    return SUCCESS;
}
