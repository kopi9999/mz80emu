#include "unitTest.h"

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
