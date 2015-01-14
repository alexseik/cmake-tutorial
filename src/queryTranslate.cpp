#include <boost/regex.hpp>

#include "queryTranslate.h"


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


