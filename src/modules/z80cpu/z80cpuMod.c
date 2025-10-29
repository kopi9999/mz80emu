#include "z80cpuMod.h"

const char* moduleName = "Z80 CPU module";
const char* moduleDescription = "Module emulating Z80 CPU";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;
const uint16_t interfacesNumber = 1;
const char* interfacesDescriptions[] = {};

enum Error create(void** instance, void*__restrict parameters)
{
    struct Instance* instanceTmp = calloc(1, sizeof(struct Instance));
    *instance = (void*) instanceTmp;
    
    return SUCCESS;
}

enum Error createInterfaces(void*__restrict instance, void*** interfaces, uint16_t*__restrict count)
{
    *interfaces = calloc(15, sizeof(void*));
    if (!*interfaces) {return MALLOC_ERROR;}

    (*interfaces)[0] = calloc(1, sizeof(uint16_t)); // address bus
    if (!(*interfaces)[0]) {return MALLOC_ERROR;}
    
    (*interfaces)[1] = calloc(1, sizeof(uint8_t)); // data bus
    if (!(*interfaces)[1]) {return MALLOC_ERROR;}
    
    (*interfaces)[2] = calloc(1, sizeof(uint8_t)); // m1
    if (!(*interfaces)[2]) {return MALLOC_ERROR;}

    (*interfaces)[3] = calloc(1, sizeof(uint8_t)); // mreq
    if (!(*interfaces)[3]) {return MALLOC_ERROR;}
    
    (*interfaces)[4] = calloc(1, sizeof(uint8_t)); // iorq
    if (!(*interfaces)[4]) {return MALLOC_ERROR;}
    
    (*interfaces)[5] = calloc(1, sizeof(uint8_t)); // rd
    if (!(*interfaces)[5]) {return MALLOC_ERROR;}
    
    (*interfaces)[6] = calloc(1, sizeof(uint8_t)); // wr
    if (!(*interfaces)[6]) {return MALLOC_ERROR;}
    
    (*interfaces)[7] = calloc(1, sizeof(uint8_t)); // rfsh
    if (!(*interfaces)[7]) {return MALLOC_ERROR;}
    
    (*interfaces)[8] = calloc(1, sizeof(uint8_t)); // halt
    if (!(*interfaces)[8]) {return MALLOC_ERROR;}
    
    (*interfaces)[9] = calloc(1, sizeof(uint8_t)); // wait
    if (!(*interfaces)[9]) {return MALLOC_ERROR;}
    
    (*interfaces)[10] = calloc(1, sizeof(uint8_t)); // int
    if (!(*interfaces)[10]) {return MALLOC_ERROR;}
    
    (*interfaces)[11] = calloc(1, sizeof(uint8_t)); // nmi
    if (!(*interfaces)[11]) {return MALLOC_ERROR;}
    
    (*interfaces)[12] = calloc(1, sizeof(uint8_t)); // reset
    if (!(*interfaces)[12]) {return MALLOC_ERROR;}
    
    (*interfaces)[13] = calloc(1, sizeof(uint8_t)); // busrq
    if (!(*interfaces)[13]) {return MALLOC_ERROR;}
    
    (*interfaces)[14] = calloc(1, sizeof(uint8_t)); // busack
    if (!(*interfaces)[14]) {return MALLOC_ERROR;}
    
    *count = 15;
    return SUCCESS;
}

enum Error strobeUp(void*__restrict instance, void**__restrict interfaces)
{
    struct Instance* instanceTmp = instance;

    if(instanceTmp->MState == 0 && instanceTmp->TCycle == 0){ // new cycle
        instanceTmp->MState = 1;
        instanceTmp->TCycle = 1;
        *(uint8_t*) interfaces[2] = 1; // m1
        *(uint16_t*) interfaces[0] = instanceTmp->PC;
        return SUCCESS;
    }

    if (instanceTmp->MState == 1){
       if (instanceTmp->TCycle == 1){
            instanceTmp->TCycle = 2;
            return SUCCESS;
        }
        if (instanceTmp->TCycle == 2) {
            instanceTmp->instruction = *(uint8_t*) interfaces[1];
            *(uint8_t*) interfaces[2] = 0; // m1
            *(uint8_t*) interfaces[3] = 0; // mreq
            *(uint8_t*) interfaces[5] = 0; // rd
            *(uint8_t*) interfaces[7] = 1; // rfsh
            instanceTmp->TCycle = 3;
            return SUCCESS;
        }
        if (instanceTmp->TCycle == 3) {
            instanceTmp->TCycle = 4;
            return SUCCESS;
        }
        if (instanceTmp->TCycle == 4) {
            printf("\nLoaded instruction %d on address %d", instanceTmp->instruction, instanceTmp->PC);
            instanceTmp->PC++;
            instanceTmp->MState = 0;
            instanceTmp->TCycle = 0;
            *(uint8_t*) interfaces[7] = 0; // rfsh
            return SUCCESS;
        }
    }
    return SUCCESS;
}

enum Error strobeDown(void*__restrict instance, void**__restrict interfaces)
{
    struct Instance* instanceTmp = instance;

    if (instanceTmp->MState == 1){
        if (instanceTmp->TCycle == 1){
            *(uint8_t*) interfaces[3] = 1; // mreq
            *(uint8_t*) interfaces[5] = 1; // rd
            return SUCCESS;
        }
        if (instanceTmp->TCycle == 2) {return SUCCESS;}
        if (instanceTmp->TCycle == 3) {
            *(uint8_t*) interfaces[3] = 1; // mreq
            return SUCCESS;
        }
        if (instanceTmp->TCycle == 4){
            *(uint8_t*) interfaces[3] = 0; // mreq
            return SUCCESS;
        }
    }
    
    return SUCCESS;
}

enum Error destroy(void* instance)
{
    if (!instance) {return BAD_ARGUMENT;}
    free(instance);
    return SUCCESS;
}

enum Error destroyInterfaces(void*__restrict instance, void** interfaces, uint16_t count)
{
    if (!instance) {return BAD_ARGUMENT;}
    if (!interfaces) {return BAD_ARGUMENT;}
    
    for (uint8_t i = 0; i < 15; i++) {
        free(interfaces[i]);
    }
    free(interfaces);

    return SUCCESS;
}
