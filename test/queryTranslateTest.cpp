#define BOOST_TEST_MODULE QueryTranslateTests
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "queryTranslate.h"


BOOST_AUTO_TEST_CASE(PassRegex)
{
    const std::string text ("ELSE");
    BOOST_CHECK(acceptElse(text));

    const std::string text2 ("Another thing");
    BOOST_CHECK(!acceptElse(text2));
}
