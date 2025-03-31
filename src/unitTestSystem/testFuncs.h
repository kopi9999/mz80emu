#ifndef TEST_MODULES
#define TEST_MODULES 2

#include "unitTest.h"

#include "../modules/test/unitTests/test.h"
#include "../unitTests/main.h"

struct UnitTestModuleResult (*testFuncs[TEST_MODULES])() = {testTestDll, testMain};
char* names[TEST_MODULES] = {"testTestDll", "testMain"};

#endif
