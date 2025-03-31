#include "testFuncs.h"
uint16_t iterateTests(char* names[], bool (*funcs[])(), uint16_t tests)
{
    uint16_t fails = 0;
    for (uint16_t i = 0; i < tests; ++i){
        printf("\t%s: ", names[i]);
        if (funcs[i]()){
            printf("PASS\n");
            continue;
        }
        ++fails;
        printf("FAIL\n");
    }
    printf("\t\t%u tests ran, %u failed", tests, fails);
    return fails;
}

int main(){
    struct UnitTestModuleResult response;
    uint32_t tests = 0;
    uint32_t fails = 0;
    for (uint16_t i = 0; i < TEST_MODULES; i++){
        printf("\n\nTesting %s:\n", names[i]);
        response = testFuncs[i]();
        tests += response.tests;
        fails += response.fails;
    }
    printf("\n\n%d tests ran in %d test modules, %d tests failed", tests, TEST_MODULES, fails);
    return 0;
}
