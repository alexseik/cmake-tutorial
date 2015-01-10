#include <regex>
#include <boost/regex.hpp>

#include "queryTranslate.h"

bool acceptElse(const std::string& input){
    static const boost::regex e("ELSE");
    return boost::regex_match(input, e);
}
