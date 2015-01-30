#ifndef QUERY_TRANSLATE_H
#define QUERY_TRANSLATE_H
#include <stdlib.h>
#include <boost/smart_ptr.hpp>
#include "etx2Sql.h"
#include "token.h"
//using namespace std;

static int tokenCount = 0;

EXTERNAL ETX2SQL_EXPORT bool acceptMaintable(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptOutfields(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptJoinList(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptFieldsep(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptMaxrecnum(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptCondition(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptOutfieldtypes(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool acceptStartsep(const std::string& );

EXTERNAL ETX2SQL_EXPORT bool isSeparator(char);

EXTERNAL ETX2SQL_EXPORT bool isInstructionSeparator(char);

EXTERNAL_CPP ETX2SQL_EXPORT std::vector<std::string> getInstructions(std::string&);

EXTERNAL ETX2SQL_EXPORT bool processMaintable(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processOutfields(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processCondition(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processJoinlist(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processStartsep(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processRecordsep(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processFieldsep(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processOutfieldtypes(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

EXTERNAL ETX2SQL_EXPORT bool processMaxrecnum(const std::string&, std::vector<boost::shared_ptr<CToken>>&);

#endif
