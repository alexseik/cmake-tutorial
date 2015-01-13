#ifndef QUERY_TRANSLATE_H
#define QUERY_TRANSLATE_H
#include <stdlib.h>
using namespace std;

bool acceptMaintable(const std::string& );

bool acceptOutfields(const std::string& );

bool acceptJoinList(const std::string& );

bool acceptFieldsep(const std::string& );

bool acceptMaxrecnum(const std::string& );

bool acceptCondition(const std::string& );

bool acceptOutfieldtypes(const std::string& );

bool acceptStartsep(const std::string& );

bool isSeparator(char);

#endif
