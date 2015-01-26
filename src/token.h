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
enum Kind {INSSEP,STARTSEP,FROM,SELECT,WHERE,JOIN,COND,BOOLOPE,PARAM,TNAME,FNAME,FORMATFEA,DATE,DATEEXP,IDENT};

class CToken {
	private:
		int id;
		std::string value;
		std::string symbol;
		Kind kind;
	public:
		CToken(int id, std::string value, std::string symbol, Kind kind):id(id),value(value),symbol(symbol),kind(kind){};
		int getId(){return id;};
		std::string getValue(){return value;};
		std::string getSymbol(){return symbol;};
		Kind getKind(){return kind;};
};
