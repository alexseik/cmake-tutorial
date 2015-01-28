//#include <iostream>
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

bool processOutfields(const std::string& instruction, std::vector<boost::shared_ptr<CToken>>& tokens)
{
	std::vector<std::string> tables;
	bool result = false;

	//split instruction by tables references, split by ";"
	boost::regex e(";");
    boost::sregex_token_iterator i(instruction.begin(), instruction.end(), e, -1);
    boost::sregex_token_iterator j;
    unsigned count = 0;
    while(i != j)
    {
		//std::cout << *i << std::endl;
		tables.push_back(*i++);		
        count++;
    }
	if (count == 0) return false;
	//std::cout << "There were " << count << " instructions found." << std::endl;
	
	//test instruction begins with correct reserved word and erase it from instruction producing a token
	boost::regex firstRegex ("^((?i)OUTFIELDS)\\s+(.*)");
	std::string::const_iterator start, end;
	start = tables[0].begin();
	end = tables[0].end();
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	if (boost::regex_match(start,end,what,firstRegex,flags)){
		tables[0] = what[2];
		boost::shared_ptr<CToken> tokenReservedWord(new CToken(0, "OUTFIELDS", "OUTFIELDS", Kind::SELECT));
		tokens.push_back(tokenReservedWord);
		result = true;
	} else return false;

	//parse tokens from tables references found	
	boost::regex instRegex (":");	
	for (int k = 0; k<count; k++) {
		// first, split by colon ":"
		i = boost::sregex_token_iterator(tables[k].begin(), tables[k].end(), instRegex, -1);
		j = boost::sregex_token_iterator();
		std::vector<std::string> insPart;
		unsigned count1 = 0;
		while(i != j)
		{
			//std::cout << *i << std::endl;
			insPart.push_back(*i++);
			count1++;
		}
		if (count1 != 2) return false; // should be a table name and several fields
		//second, save table name into a token
		boost::trim(insPart[0]);
		boost::shared_ptr<CToken> tableName(new CToken(0, insPart[0], "TABLENAME", Kind::SELECT));
		tokens.push_back(tableName);
		//third, save field names
		boost::regex instRegex (",");
		i = boost::sregex_token_iterator(insPart[1].begin(), insPart[1].end(), instRegex, -1);
		j = boost::sregex_token_iterator();
		unsigned count2 = 0;
		while (i != j){
			std::string aux = *i++;
			boost::trim(aux);
			//std::cout << aux << std::endl;
			boost::shared_ptr<CToken> fieldName(new CToken(0, aux, "FIELDNAME", Kind::SELECT));
			tokens.push_back(fieldName);
			count2++;
		}
		if (count2 < 1) return false; //it should be at least one field
	}	
	
	return result;
}

bool processCondition(const std::string& instruction, std::vector<boost::shared_ptr<CToken>>& tokens)
{
	bool result = false;
	std::string condition;
	std::vector<std::string> conditions;
	std::vector<std::string> opers;
	//test instruction begins with correct reserved word and erase it from instruction producing a token
	boost::regex firstRegex ("^((?i)CONDITION)\\s+(.*)");
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;
	if (boost::regex_match(instruction.begin(),instruction.end(),what,firstRegex,flags)){
		condition = what[2];
		boost::shared_ptr<CToken> tokenReservedWord(new CToken(0, "CONDITION", "CONDITION", Kind::WHERE));
		tokens.push_back(tokenReservedWord);
		result = true;
	} else return false; //return false if instruction does not begin with condition
	
	//count "AND" or "OR" and save in opers.
	boost::regex e("AND|OR");
    boost::sregex_token_iterator i(condition.begin(), condition.end(), e, 0);
    boost::sregex_token_iterator j;
	int condCount = 0;	
	while(i != j)
	{
		//std::cout << *i << std::endl;
		opers.push_back(*i++);
		condCount++;
	}
	//conditions well formed
	boost::regex wellCondExp("\\s+AND\\s+|\\s+OR\\s+");
    i = boost::sregex_token_iterator (condition.begin(), condition.end(), wellCondExp, 0);
    j = boost::sregex_token_iterator ();
	int goodCondCount = 0;	
	while(i != j)
	{
		//std::cout << *i << std::endl;
		opers.push_back(*i++);
		goodCondCount++;
	}
	if (condCount != goodCondCount) {
		tokens.clear();
		return false;
	}
	//split instruction by "AND" or "OR"
    i = boost::sregex_token_iterator (condition.begin(), condition.end(), e, -1);
    j = boost::sregex_token_iterator ();
	int count = 0;	
	while(i != j)
	{
		//std::cout << *i << std::endl;
		std::string aux = *i++;
		boost::trim(aux);
		conditions.push_back(aux);
		count++;
	}
	if (count < 1 || count != condCount + 1) {// should there be a minimum of one condition
		tokens.clear();
		return false;
	} 
	//std::cout << "There were " << count << " conditions found." << std::endl;

	//for each condition parse its tokens	
	for (int k = 0; k<count; k++) {
		boost::regex ce("^(\\w+)\\s*(=|\\<|>|\\<>)\\s*(\"@\")");
		boost::match_results<std::string::const_iterator> whatOpe;
		boost::match_flag_type flags = boost::match_default;
		if (boost::regex_search(conditions[k],whatOpe,ce,flags)) {						
			if (k > 0) { // save condition
				std::string aux = opers[k-1]; // condition
				boost::trim(aux);
				boost::shared_ptr<CToken> tokenCondition(new CToken(0, aux, "CONDITION", Kind::WHERE));
				tokens.push_back(tokenCondition);
			}
			//save field name
			std::string aux = whatOpe[1]; // field submatch
			boost::trim(aux);
			boost::shared_ptr<CToken> tokenFiledName(new CToken(0, aux, "FIELDNAME", Kind::WHERE));
			tokens.push_back(tokenFiledName);
			//save operator
			aux = whatOpe[2]; // operator submatch
			boost::trim(aux);
			boost::shared_ptr<CToken> tokenOperator(new CToken(0, aux, "OPERATOR", Kind::WHERE));
			tokens.push_back(tokenOperator);
			//save parameter for use after
			aux = whatOpe[3]; // parameter submatch
			boost::trim(aux);
			boost::shared_ptr<CToken> tokenParameter(new CToken(0, aux, "PARAMETER", Kind::WHERE));
			tokens.push_back(tokenParameter);
			result = true;
		} else {
			tokens.clear();
			return false;
		}
	}
	return result;
}

bool processJoinlist(const std::string& instruction, std::vector<boost::shared_ptr<CToken>>& tokens)
{		
	std::string joinGroups;	
	boost::regex reservedWordRegex ("^((?i)JOINLIST)\\s+(.*)");
	boost::match_results<std::string::const_iterator> what;
	if (boost::regex_match(instruction.begin(),instruction.end(),what,reservedWordRegex)){		
		joinGroups = what[2];
		boost::shared_ptr<CToken> tokenReservedWord(new CToken(0, "JOINLIST", "JOINLIST", Kind::JOIN));
		tokens.push_back(tokenReservedWord);		
	} else return false; //return false if instruction does not begin with joinlist
	
	std::vector<std::string> joins;
	boost::regex joinGroupExp(";");
	boost::sregex_token_iterator i(joinGroups.begin(), joinGroups.end(), joinGroupExp, -1);
	boost::sregex_token_iterator j;
	int count = 0;	
	while(i != j)
	{
		//std::cout << *i << std::endl;
		std::string groupStr = *i++;
		boost::trim(groupStr);
		//joins.push_back(aux);
		boost::regex fieldExp(",");
		boost::sregex_token_iterator k(groupStr.begin(), groupStr.end(), fieldExp, -1);
		boost::sregex_token_iterator l;
		int pair = 0;
		while (k != l)
		{
			std::string aux = *k++;
			boost::trim(aux);
			if (pair == 0){
				  if (aux.find(':') != std::string::npos) {
					    tokens.clear();
					    return false; // first fieldname
				  }
				  boost::shared_ptr<CToken> tokenParameter(new CToken(0, aux, "FIELDNAME", Kind::JOIN));
				  tokens.push_back(tokenParameter);
			}
			else if (pair == 1){
				  boost::regex fieldExp(":");
				  boost::sregex_token_iterator m(aux.begin(), aux.end(), fieldExp, -1);
				  boost::sregex_token_iterator n;
				  int elems = 0;
				  while (m != n)
				  {
					  std::string value = *m++;
					  boost::trim(value);
					  if (elems == 0){
						    boost::shared_ptr<CToken> tokenParameter(new CToken(0, value, "TABLENAME", Kind::JOIN));
						    tokens.push_back(tokenParameter);
					  }
					  else if (elems == 1){
						    boost::shared_ptr<CToken> tokenParameter(new CToken(0, value, "FIELDNAME", Kind::JOIN));
						    tokens.push_back(tokenParameter);
					  }
					  else return false; // no more than two values in a group
					  elems++;
				  }
			}
			else return false; // no more than two values in a group
			pair++;
		}
		count++;
	}
	if (count < 1) {// should there be a minimum of one condition
		tokens.clear();
		return false;
	} 
	return true;
}
