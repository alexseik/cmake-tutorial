#define BOOST_TEST_MODULE QueryTranslateTests
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "queryTranslate.h"

BOOST_AUTO_TEST_SUITE( test_suite_querytrans )

BOOST_AUTO_TEST_CASE(ReservedWords)
{
	std::string text,text2;
		
	text = "MAINTABLE";
    BOOST_CHECK(acceptMaintable(text));	
	text2 = "Another thing";
    BOOST_CHECK(!acceptMaintable(text2));

	text = "OUTFIELDS";
    BOOST_CHECK(acceptOutfields(text));	
    BOOST_CHECK(!acceptOutfields(text2));
	
	text = "JOINLIST";
    BOOST_CHECK(acceptJoinList(text));	
    BOOST_CHECK(!acceptJoinList(text2));
		
	text = "FIELDSEP";
    BOOST_CHECK(acceptFieldsep(text));	
    BOOST_CHECK(!acceptFieldsep(text2));
		
	text = "MAXRECNUM";
    BOOST_CHECK(acceptMaxrecnum(text));	
    BOOST_CHECK(!acceptMaxrecnum(text2));
		
	text = "CONDITION";
    BOOST_CHECK(acceptCondition(text));	
    BOOST_CHECK(!acceptCondition(text2));
		
	text = "STARTSEP";
    BOOST_CHECK(acceptStartsep(text));	
    BOOST_CHECK(!acceptStartsep(text2));
		
	text = "OUTFIELDTYPES";
    BOOST_CHECK(acceptOutfieldtypes(text));	
    BOOST_CHECK(!acceptOutfieldtypes(text2));    	
}

BOOST_AUTO_TEST_CASE(GetToken)
{
	//test on isSeparator
	char tokenSep = ';';
	BOOST_CHECK(isSeparator(tokenSep));
	tokenSep = ',';
	BOOST_CHECK(isSeparator(tokenSep));
	tokenSep = ':';
	BOOST_CHECK(isSeparator(tokenSep));
	tokenSep = '\x020';
	BOOST_CHECK(isSeparator(tokenSep));	
	tokenSep = '1';
	BOOST_CHECK(!isSeparator(tokenSep));	
	tokenSep = 'a';
	BOOST_CHECK(!isSeparator(tokenSep));
	tokenSep = '\n';
	BOOST_CHECK(!isSeparator(tokenSep));
}

BOOST_AUTO_TEST_SUITE_END()
