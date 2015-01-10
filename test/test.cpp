#define BOOST_TEST_MODULE SqrTests
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "sqr.h"
#include "queryTranslate.h"


BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(4, sqrpep(2));
}




