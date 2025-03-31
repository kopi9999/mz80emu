#ifndef UNIT_TESTS
#define UNIT_TESTS

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

struct UnitTestModuleResult {
    uint16_t tests;
    uint16_t fails;
}; 

extern uint16_t iterateTests(char* [], bool (*[])(), uint16_t);

#endif

