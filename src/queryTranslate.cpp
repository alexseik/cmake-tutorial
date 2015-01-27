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
/*
std::string getFirstTokenString(std::string& input){	
	char i = input[0];	
	std::string aux = "";
	aux += i;
	static const boost::regex blank("[[:blank:]]");
	while(boost::regex_match(aux, blank)){
		aux = "";		
		aux += input[1];
		input.erase(0,1);
	}
	aux = "";
	while(!isSeparator(i) && !isInstructionSeparator(i)){
		aux += i;
		input.erase(0,1);
		i = input[0];
	}
	return aux;
}*/

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
/*
boost::shared_ptr<CToken> getFirstToken(std::string& input){
	std::string tokenStr = getFirstTokenString(input);	
	return produceToken(tokenStr);
}*/
/*
boost::shared_ptr<CToken> produceToken(std::string& tokenStr){
	
	if (acceptMaintable(tokenStr)){
		boost::shared_ptr<CToken> token(new CToken(tokenCount++,tokenStr,tokenStr,FROM));
		return token;
	}
	if (acceptStartsep(tokenStr)){
		boost::shared_ptr<CToken> token(new CToken(tokenCount++,tokenStr,tokenStr,FROM));
		return token;
	}
	return NULL;
}*/



