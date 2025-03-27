#ifndef TEST_MODULES
#define TEST_MODULES 1

#include "unitTest.h"

#include "../modules/test/unitTests/test.h"

struct UnitTestModResult (*testFuncs[TEST_MODULES])() = {testTestDll};
char* names[TEST_MODULES] = {"testTestDll"};

#endif
