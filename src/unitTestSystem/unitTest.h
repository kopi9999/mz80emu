#ifndef UNIT_TEST_LIB
#define UNIT_TEST_LIB

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

size_t (*runFuncts[2])();

extern void iterateTests(char* [], bool (*[])(), uint16_t);

#endif
