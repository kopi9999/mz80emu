#include "memoryMod.h"

const char* moduleName = "memory";
const char* moduleDescription = "Emulates 64kB of memory";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;
const uint16_t interfacesNumber = 1;
const char* interfacesDescriptions[] = {};

enum Error create(void** instance, void*__restrict parameters)
{
    return SUCCESS;
}


enum Error createInterfaces(void*__restrict instance, void*** interfaces, uint16_t*__restrict count)
{
    return SUCCESS;
}

enum Error strobeUp(void*__restrict instance, void**__restrict interfaces)
{
    return SUCCESS;
}

enum Error strobeDown(void*__restrict instance, void**__restrict interfaces)
{
    return SUCCESS;
}

enum Error destroy(void* instance)
{
    return SUCCESS;
}

enum Error destroyInterfaces(void*__restrict instance, void** interfaces, uint16_t count)
{
    return SUCCESS;
}
