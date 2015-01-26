#define BOOST_TEST_MODULE QueryTranslateTests
#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include <boost/smart_ptr.hpp>
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

BOOST_AUTO_TEST_CASE(TokenSeparators)
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

BOOST_AUTO_TEST_CASE(InstructionSeparators)
{
	//test on isSeparator
	char tokenSep = '\n';
	BOOST_CHECK(isInstructionSeparator(tokenSep));
	tokenSep = '|';
	BOOST_CHECK(isInstructionSeparator(tokenSep));
	tokenSep = ':';
	BOOST_CHECK(!isInstructionSeparator(tokenSep));
	tokenSep = '\x020';
	BOOST_CHECK(!isInstructionSeparator(tokenSep));	
	tokenSep = '1';
	BOOST_CHECK(!isInstructionSeparator(tokenSep));		
}

BOOST_AUTO_TEST_CASE(getFirstTokenStringTest)
{
	std::string instructions,token;
	// good instructions	
	instructions = "STARTSEP \"\"|FIELDSEP \",\"|RECORDSEP \"\\r\\n\"|MAXRECNUM 1|MAINTABLE FCOPTS1.DAT|";
	token = getFirstTokenString(instructions);
	BOOST_CHECK(token == "STARTSEP");
	// care about spaces before token
	instructions = " \"\"|FIELDSEP \",\"|RECORDSEP \"\\r\\n\"|MAXRECNUM 1|MAINTABLE FCOPTS1.DAT|";
	token = getFirstTokenString(instructions);
	BOOST_CHECK(token == "\"\"");
	//bad instructions
}

BOOST_AUTO_TEST_CASE(getInstructionsTest)
{
	std::string instructions,result,token;
	std::vector<std::string> instructionSet;
	
	instructions = "STARTSEP \"\"|FIELDSEP \",\"|RECORDSEP \"\\r\\n\"|MAXRECNUM 1|MAINTABLE FCOPTS1.DAT|"
		"holalfdsafdsafdsaf\r\nf�lakjfa�slfkjd\nsaf";
	instructionSet = getInstructions(instructions);
	BOOST_CHECK(instructionSet[0] == "STARTSEP \"\"");
	BOOST_CHECK(instructionSet[1] == "FIELDSEP \",\"");	
	BOOST_CHECK(instructionSet[2] == "RECORDSEP \"\\r\\n\"");	
	BOOST_CHECK(instructionSet[3] == "MAXRECNUM 1");	
	BOOST_CHECK(instructionSet[4] == "MAINTABLE FCOPTS1.DAT");	
	BOOST_CHECK(instructionSet[5] == "holalfdsafdsafdsaf");	
	BOOST_CHECK(instructionSet[6] == "f�lakjfa�slfkjd");	
	BOOST_CHECK(instructionSet[7] == "saf");	
}


BOOST_AUTO_TEST_CASE(getFirstTokenTest)
{
	std::string instructions;
	boost::shared_ptr<CToken> token;
	// good instructions
	instructions = "STARTSEP \"\"|FIELDSEP \",\"|RECORDSEP \"\\r\\n\"|MAXRECNUM 1|MAINTABLE FCOPTS1.DAT|";
	token = getFirstToken(instructions);
	BOOST_CHECK(token->getSymbol() == "STARTSEP");
	//bad instructions
}

BOOST_AUTO_TEST_SUITE_END()
