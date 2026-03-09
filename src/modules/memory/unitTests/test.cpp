#define BOOST_TEST_MODULE testTestDll
#include <boost/test/included/unit_test.hpp>

extern "C" {
    #include "../memoryMod.h"
}

BOOST_AUTO_TEST_SUITE( testMemoryModule )

BOOST_AUTO_TEST_SUITE_END()
