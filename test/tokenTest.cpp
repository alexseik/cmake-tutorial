#include <boost/test/unit_test.hpp>
#include <boost/smart_ptr.hpp>

#include "token.h"

BOOST_AUTO_TEST_SUITE( test_suite_token )

BOOST_AUTO_TEST_CASE(createTokenTest)
{
	Kind tipo = INSSEP;
	boost::scoped_ptr<CToken> token(new CToken(1,"loque me sale","MAINTABLE",tipo));	
	BOOST_CHECK(token->getId() == 1);	
}

BOOST_AUTO_TEST_SUITE_END()