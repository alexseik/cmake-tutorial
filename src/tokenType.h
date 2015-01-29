#pragma once
#include <string>
/**
* INSSEP : instruction separator
* STARTSEP : token for STARTSEP reserved word
* FIELDSEP : token for FIELDSEP reserved word
* RECORDSEP : token for RECORDSEP reserved word
* MAXRECNUM : token for MAXRECNUM reserved word
* FROM : token for MAINTABLE reserved word
* SELECT : token for OUTFIELDS reserved word
* WHERE : token for CONDITION reserved word
* JOIN : token for JOINLIST reserved word
* COND : token for =,<,>,<> reserved words
* BOOLOPE : token for AND,OR reserved words
* PARAM : token for "@" reserved word
* TNAME : token for table name identifiers
* FNAME : token for field name identifiers
* FORMATFEA : token for format features like RTRIM,LTRIM,NORTRIM,NOLTRIM
* DATE : token for DATE reserved word
* DATEEXP : token for date format expressions
* IDENT : token for identifiers of fields, tables and values
*/

namespace TokenInstruction {
	/**
	* Types of instructions existing in ETXQuery language.
	*/
	enum Instruction{		
		STARTSEP, 
		FIELDSEP,
		RECORDSEP,
		FROM,
		SELECT,
		OUTFIELDTYPES,
		WHERE,
		JOIN,
		MAXRECNUM
	};
};


namespace TokenSymbol {

	/**
	* Types of reserved words existing in ETXQuery language.
	*/
	enum Symbol {
		INSSEP,	/* Instruction separator, | or break line*/			
		COND, /* Condition reserved word : AND / OR*/
		BOOLOPE, /* Token for =,<,>,<> reserved words*/
		PARAM, /* Token for "@" reserved word*/
		TNAME, /* Token for table name identifiers*/
		FNAME, /* Token for field name identifiers*/
		FORMATFEA, /* Token for format features like RTRIM,LTRIM,NORTRIM,NOLTRIM*/
		RAW, /* Token for RAW reserved word in Outfieldtypes instruction */
		DUMMY, /* Token for DUMMY reserved word in Outfieldtypes instruction */
		DATE, /* Token for DATE reserved word in Outfieldtypes instruction */
		DATEEXP, /* Token for a date expression yyyy/mm/dd ddmmyyyy DMyyS*/
		IDENT, /* Token for identificators.... not really neccessary */
		TK_MAINTABLE, /* Token for reserved word MAINTABLE */
		TK_OUTFIELDS, /* Token for reserved word OUTFIELDS */
		TK_CONDITION, /* Token for reserved word CONDITION */
		TK_JOINLIST, /* Token for reserved word JOINLIST */
		TK_STARTSEP, /* Token for reserved word STARTSEP */
		TK_RECORDSEP, /* Token for reserved word RECORDSEP */
		TK_FIELDSEP, /* Token for reserved word FIELDSEP */
		TK_OUTFIELDTYPES, /* Token for reserved word OUTFIELDTYPES*/
		VALUE /* Token for a value of foregoing token */
	};
};