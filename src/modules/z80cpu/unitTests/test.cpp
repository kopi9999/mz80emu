#define BOOST_TEST_MODULE testTestDll
#include <boost/test/included/unit_test.hpp>

extern "C" {
    #include "../z80cpuMod.h"
}

BOOST_AUTO_TEST_SUITE( testTestDll )
BOOST_AUTO_TEST_SUITE_END()
