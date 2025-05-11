#ifndef TEST_MODULES
#define TEST_MODULES 3

#include "unitTest.h"

#include "../modules/test/unitTests/test.h"
#include "../unitTests/misc.h"
#include "../unitTests/init.h"

struct UnitTestModuleResult (*testFuncs[TEST_MODULES])() = {testTestDll, testMisc, testInit};
char* names[TEST_MODULES] = {"testTestDll", "testMisc", "tesInit"};

#endif
