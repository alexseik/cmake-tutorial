#define BOOST_TEST_MODULE QueryTranslateTests
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "queryTranslate.h"

BOOST_AUTO_TEST_SUITE( test_suite_querytrans )

BOOST_AUTO_TEST_CASE(ElseRegex)
{
    const std::string text ("ELSE");
    BOOST_CHECK(acceptElse(text));

    const std::string text2 ("Another thing");
    BOOST_CHECK(!acceptElse(text2));
}

BOOST_AUTO_TEST_CASE(MaintableRegex)
{
    const std::string text ("MAINTABLE");
    BOOST_CHECK(acceptMaintable(text));

    const std::string text2 ("Another thing");
    BOOST_CHECK(!acceptMaintable(text2));
}

BOOST_AUTO_TEST_CASE(OUTFIELDSRegex)
{
    const std::string text ("OUTFIELDS");
    BOOST_CHECK(acceptOutfields(text));

    const std::string text2 ("Another thing");
    BOOST_CHECK(!acceptOutfields(text2));
}

BOOST_AUTO_TEST_SUITE_END()
