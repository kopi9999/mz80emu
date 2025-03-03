#include "misc.h"

uint16_t firstNullPointer (void** __restrict tab, uint16_t count)
{
    for (uint16_t i = 0; i < count; i++){
        if (tab[i] == NULL) {return i;}
    }
    return count;
}
