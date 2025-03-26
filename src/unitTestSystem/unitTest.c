#include "unitTest.h"
#include "getTestFuncs.h"

void iterateTests(char* names[], bool (*funcs[])(), uint16_t length)
{
    uint16_t fails = 0;
    for (uint16_t i = 0; i < length; ++i){
        printf("\t%s: ", names[i]);
        if (funcs[i]()){
            printf("PASS\n");
            continue;
        }
        ++fails;
        printf("FAIL\n");
    }
    printf("\t\t%u tests ran, %u failed", length, fails);
}

int main(){
    uint32_t tests = 0;
    for (uint16_t i = 0; i < TESTS; i++){
        printf("\n\nTesting %s:\n", names[i]);
        tests += testFuncs[i]();
    }
    printf("\n%d tests ran", tests);
    return 0;
}
