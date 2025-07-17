#include "moduleInternal.h"
#include <string.h>

enum Error getName(char* out, uint32_t maxLength)
{
    if(out == NULL) {return BAD_ARGUMENT;}
    if(strlen(moduleName) > maxLength){return SIZE_MISMATCH;}
    strcpy(out, moduleName);
    return SUCCESS; 
}

enum Error getDescription(char* out, uint32_t maxLength)
{
    if(out == NULL) {return BAD_ARGUMENT;}
    if(strlen(moduleDescription) > maxLength){return SIZE_MISMATCH;}
    strcpy(out, moduleDescription);
    return SUCCESS; 
}
