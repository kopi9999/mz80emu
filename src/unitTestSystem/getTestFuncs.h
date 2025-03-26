#ifndef TESTS
#define TESTS 1

#include <stdint.h>
#include "../modules/test/unitTests/test.h"

extern uint16_t (*testFuncs[TESTS])();
extern char* names[TESTS];

uint16_t (*testFuncs[TESTS])() = {testTestDll};
char* names[TESTS] = {"testDll"};
#endif
