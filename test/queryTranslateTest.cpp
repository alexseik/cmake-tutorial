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

BOOST_AUTO_TEST_CASE(getInstructionsTest)
{
	std::string instructions,result,token;
	std::vector<std::string> instructionSet;

	// test vertical line like separator
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

	//test line break like separator
	instructions = 
		"MAINTABLE  086.DAT\r\n"
		"OUTFIELDS  086.DAT:KUGRP1,KUGRP2,KUGRP3,KUGRP4,KUGRP5,KUGRP6,KUGRP7,LACKCODE\r\n"
		"CONDITION  TYPCODE = \"@\"";
	instructionSet = getInstructions(instructions);
	BOOST_CHECK(instructionSet[0] == "MAINTABLE  086.DAT");
	BOOST_CHECK(instructionSet[1] == "OUTFIELDS  086.DAT:KUGRP1,KUGRP2,KUGRP3,KUGRP4,KUGRP5,KUGRP6,KUGRP7,LACKCODE");	
	BOOST_CHECK(instructionSet[2] == "CONDITION  TYPCODE = \"@\"");

	//test trimed instruction returned
	instructions = 
		"MAINTABLE  086.DAT |"
		"OUTFIELDS  086.DAT:KUGRP1,KUGRP2,KUGRP3,KUGRP4,KUGRP5,KUGRP6,KUGRP7,LACKCODE \r\n"
		"CONDITION  TYPCODE = \"@\"";
	instructionSet = getInstructions(instructions);
	BOOST_CHECK(instructionSet[0] == "MAINTABLE  086.DAT");
	BOOST_CHECK(instructionSet[1] == "OUTFIELDS  086.DAT:KUGRP1,KUGRP2,KUGRP3,KUGRP4,KUGRP5,KUGRP6,KUGRP7,LACKCODE");	
	BOOST_CHECK(instructionSet[2] == "CONDITION  TYPCODE = \"@\"");
}


BOOST_AUTO_TEST_CASE(processMaintableTest)
{
	bool result;
	std::vector<boost::shared_ptr<CToken>> tokens;

	// test true if instruction begins by Maintable
	std::string inst = "MAInTaBLE 011.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 2);
	tokens.clear();

	inst = "MAINTABLE 011.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 2);
	tokens.clear();

	inst = "maintable FCMLGCAT.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 2);
	tokens.clear();

	inst = "MAINTABLE FZTYP.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 2);
	tokens.clear();

	//test trim on table identifier
	inst = "MAINTaBLE   VAT.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 2);
	BOOST_CHECK(tokens[1]->getValue() == "VAT.DAT");	
	tokens.clear();

	//test false if instruction doesn't begin by maintable
	inst = "MAINABLE FZTYP.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == false);
	//instructions have to be trimmed by the instructor separator
	inst = "    MAINABLE FZTYP.DAT";
	result = processMaintable (inst,tokens);
	BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(processOutfieldsTest)
{
	bool result;
	std::vector<boost::shared_ptr<CToken>> tokens;

	//test false if instruction does not begin with outfields
	std::string inst = "OUTFILDS VAT.DAT:VATVALID, VATVAL, TRANCA;VATLIST.DAT:INCLEXCL";
	result = processOutfields (inst,tokens);
	BOOST_CHECK(result == false);

	//instructions have to be trimmed by the instructor separator	
	inst = " OUTFIELDS VAT.DAT:VATVALID, VATVAL, TRANCA;VATLIST.DAT:INCLEXCL";
	result = processOutfields (inst,tokens);
	BOOST_CHECK(result == false);

	//test true if instruction begins by Outfields
	inst = "OUTFIELDS FZTYP.DAT:LETZTNPD";
	result = processOutfields(inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 3);
	tokens.clear();

	//test multiples tables in select(OUTFIELDS) instruciton
	inst = "OUTFIELDS VAT.DAT:VATVALID, VATVAL, TRANCA;VATLIST.DAT:INCLEXCL";
	result = processOutfields (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 7);
	tokens.clear();	

	inst = "OUTFIELDS     VAT.DAT:VATVALID, VATVAL, TRANCA;VATLIST.DAT:INCLEXCL; AUTOMAT.DAT:CACHONDO,LISTO";
	result = processOutfields (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 10);
	tokens.clear();

	inst = "OUTFIELDS     VAT.DAT:    VATVALID  , VATVAL, TRANCA  ;VATLIST.DAT:INCLEXCL; AUTOMAT.DAT:CACHONDO,LISTO";
	result = processOutfields (inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 10);
	BOOST_CHECK(tokens[7]->getValue() == "AUTOMAT.DAT");
	tokens.clear();
}

BOOST_AUTO_TEST_CASE(processConditionTest)
{
	bool result;
	std::vector<boost::shared_ptr<CToken>> tokens;

	//test true if instruction begins with condition
	std::string inst = "CONDITION TYPNR = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 4);
	tokens.clear();

	//test true with multiple conditions and spaces
	inst = "CONDITION KUCODE = \"@\" AND HGR = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 8);
	tokens.clear();

	inst = "CONdiTiON KUCODE = \"@\" AND HGR = \"@\" OR CACA = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens[4]->getValue() == "AND");
	BOOST_CHECK(tokens.size() == 12);
	tokens.clear();

	inst = "CONDITION KUCODE= \"@\"    AND HGR =\"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == true);
	BOOST_CHECK(tokens.size() == 8);
	tokens.clear();

	//test false if intruction does not begin with CONDITION
	inst = "CONdiTON KUCODE = \"@\" AND HGR = \"@\" OR CACA = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == false);
	BOOST_CHECK(tokens.empty());
	tokens.clear();

	inst = "    CONdiTiON KUCODE = \"@\" AND HGR = \"@\" OR CACA = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == false);
	BOOST_CHECK(tokens.empty());
	tokens.clear();

	//test false if AND or OR condition is collated
	inst = "CONDITION KUCODE = \"@\"AND HGR = \"@\" OR CACA = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == false);
	BOOST_CHECK(tokens.empty());
	tokens.clear();

	inst = "CONDITION KUCODE = \"@\" ANDHGR = \"@\" OR CACA = \"@\"";
	result = processCondition(inst,tokens);
	BOOST_CHECK(result == false);
	BOOST_CHECK(tokens.empty());
	tokens.clear();
}

BOOST_AUTO_TEST_SUITE_END()
