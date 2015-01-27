#include <boost/regex.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include "queryTranslate.h"
#include "token.h"


bool acceptMaintable(const std::string& input){
    static const boost::regex e("MAINTABLE");
    return boost::regex_match(input, e);
}

bool acceptOutfields(const std::string& input){
    static const boost::regex e("OUTFIELDS");
    return boost::regex_match(input, e);
}

bool acceptJoinList(const std::string& input){
    static const boost::regex e("JOINLIST");
    return boost::regex_match(input, e);
}

bool acceptCondition(const std::string& input){
    static const boost::regex e("CONDITION");
    return boost::regex_match(input, e);
}

bool acceptOutfieldtypes(const std::string& input){
    static const boost::regex e("OUTFIELDTYPES");
    return boost::regex_match(input, e);
}

bool acceptStartsep(const std::string& input){
    static const boost::regex e("STARTSEP");
    return boost::regex_match(input, e);
}

bool acceptMaxrecnum(const std::string& input){
    static const boost::regex e("MAXRECNUM");
    return boost::regex_match(input, e);
}

bool acceptFieldsep(const std::string& input){
    static const boost::regex e("FIELDSEP");
    return boost::regex_match(input, e);
}

bool isSeparator(char input){
	std::string aux;
	aux = aux + input;
	static const boost::regex sep("[,;:]|[[:blank:]]");
	return boost::regex_match(aux, sep);
}

bool isInstructionSeparator(char input){
	std::string aux;
	aux = aux + input;
	static const boost::regex sep("[[.vertical-line.]]|[[.newline.]]");
	return boost::regex_match(aux, sep);
}

std::vector<std::string> getInstructions(std::string& input){
	std::vector<std::string> aux;
	boost::regex re ("\\||(\\n|\\r\\n)");
	boost::sregex_token_iterator i (input.begin(),input.end(),re,-1);
	boost::sregex_token_iterator j;
	//unsigned count = 0;
	while (i != j){
		std::string inst = *i++;
		boost::trim(inst);
		aux.push_back(inst);
		//count++;
	}	
	return 	aux;
}

bool processMaintable(const std::string& instruction, std::vector<boost::shared_ptr<CToken>>& tokens)
{
	boost::regex re ("((?i)MAINTABLE)(\\s+\\w+(.DAT)?)");
	boost::smatch what;

	bool result = boost::regex_match(instruction.begin(),instruction.end(), what, re);
	if (result) {
		std::string ident(what[1].first, what[1].second);
		std::string value(what[2].first, what[2].second);
		boost::shared_ptr<CToken> tokenReservedWord(new CToken(0, "MAINTABLE", "MAINTABLE", Kind::FROM));
		tokens.push_back(tokenReservedWord);
		boost::trim(value);
		boost::shared_ptr<CToken> tokenIden(new CToken(0, value, "IDENTIFIER", Kind::FROM));
		tokens.push_back(tokenIden);
		return true;
	}
	return false;
}
