#include "mOperations.h"
#include "decode.h"
#include "execute.h"

enum Error m1_strobeUp (struct Instance* __restrict instance, void** __restrict interfaces) 
{
    if (instance->TCycle == 1){
        instance->TCycle = 2;
        return SUCCESS;
    }
    if (instance->TCycle == 2) {
        instance->instruction = *(uint8_t*) interfaces[1];
        *(uint8_t*) interfaces[2] = 0; // m1
        *(uint8_t*) interfaces[3] = 0; // mreq
        *(uint8_t*) interfaces[5] = 0; // rd
        *(uint8_t*) interfaces[7] = 1; // rfsh
        instance->TCycle = 3;
        return SUCCESS;
    }
    if (instance->TCycle == 3) {
        instance->TCycle = 4;
        return SUCCESS;
    }
    if (instance->TCycle == 4) {
        instance->state = decodeInstruction(instance);
        printf("\nLoaded instruction %d on address %d, decoded to %d", instance->instruction, instance->PC, instance->state);
        instance->PC++;
        instance->MState = 0;
        instance->TCycle = 0;
        *(uint8_t*) interfaces[7] = 0; // rfsh
        return execute(instance, interfaces);
    }
    return SUCCESS;
}

enum Error m1_strobeDown (struct Instance* __restrict instance, void** __restrict interfaces) 
{
    if (instance->TCycle == 1){
        *(uint8_t*) interfaces[3] = 1; // mreq
        *(uint8_t*) interfaces[5] = 1; // rd
        return SUCCESS;
    }
    if (instance->TCycle == 2) {return SUCCESS;}
    if (instance->TCycle == 3) {
        *(uint8_t*) interfaces[3] = 1; // mreq
        return SUCCESS;
    }
    if (instance->TCycle == 4){
        *(uint8_t*) interfaces[3] = 0; // mreq
        return SUCCESS;
    }
    return SUCCESS;
}

enum Error m2_strobeUp (struct Instance* __restrict instance, void** __restrict interfaces) {
    if (instance->TCycle == 1) {instance->TCycle = 2; return SUCCESS;} 
    if (instance->TCycle == 2) {instance->TCycle = 3; return SUCCESS;} 
    if (instance->TCycle == 3) {instance->TCycle = 1; return SUCCESS;} 

    return SUCCESS;
}

enum Error m2_strobeDown (struct Instance* __restrict instance, void** __restrict interfaces) {
    
    if (instance->TCycle == 1) {
        *(uint8_t*) interfaces[3] = 1; // mreq
        *(uint8_t*) interfaces[5] = 1; // rd
        return SUCCESS;
    } 
    if (instance->TCycle == 2) {
        return SUCCESS;
    } 
    if (instance->TCycle == 3) {
        *(uint8_t*) interfaces[3] = 0; // mreq
        *(uint8_t*) interfaces[5] = 0; // rd
        instance->tmp = *(uint8_t*) interfaces[1];
        return SUCCESS;
    } 
    return SUCCESS;
}

enum Error m3_strobeUp (struct Instance* __restrict instance, void** __restrict interfaces) {
    if (instance->TCycle == 1) {instance->TCycle = 2; return SUCCESS;} 
    if (instance->TCycle == 2) {instance->TCycle = 3; return SUCCESS;} 
    if (instance->TCycle == 3) {instance->TCycle = 1; return SUCCESS;} 
    return SUCCESS;
}

enum Error m3_strobeDown (struct Instance* __restrict instance, void** __restrict interfaces) {
    if (instance->TCycle == 1) {
        *(uint8_t*) interfaces[3] = 1; // mreq
        *(uint8_t*) interfaces[1] = instance->tmp; //data
        return SUCCESS;
    } 
    if (instance->TCycle == 2) {
        *(uint8_t*) interfaces[6] = 1; // wr
        return SUCCESS;
    } 
    if (instance->TCycle == 3) {
        *(uint8_t*) interfaces[3] = 0; // mreq
        *(uint8_t*) interfaces[6] = 0; // wr
        return SUCCESS;
    } 
    return SUCCESS;
}

