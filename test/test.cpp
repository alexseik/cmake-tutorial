#define BOOST_TEST_MODULE SqrTests
#include <boost/test/unit_test.hpp>

#include "sqr.h"

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(4, sqrpep(2));
}


