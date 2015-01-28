#ifndef QUERY_TRANSLATE_H
#define QUERY_TRANSLATE_H
#include <stdlib.h>
#include <boost/smart_ptr.hpp>
#include "token.h"
//using namespace std;

static int tokenCount = 0;

bool acceptMaintable(const std::string& );

bool acceptOutfields(const std::string& );

bool acceptJoinList(const std::string& );

bool acceptFieldsep(const std::string& );

bool acceptMaxrecnum(const std::string& );

bool acceptCondition(const std::string& );

bool acceptOutfieldtypes(const std::string& );

bool acceptStartsep(const std::string& );

bool isSeparator(char);

bool isInstructionSeparator(char);

std::vector<std::string> getInstructions(std::string&);

bool processMaintable(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

bool processOutfields(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

bool processCondition(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

#endif
