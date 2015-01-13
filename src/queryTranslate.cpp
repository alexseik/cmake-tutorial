#include <boost/regex.hpp>

#include "queryTranslate.h"

bool acceptElse(const std::string& input){
    static const boost::regex e("ELSE");
    return boost::regex_match(input, e);
}

bool acceptMaintable(const std::string& input){
    static const boost::regex e("MAINTABLE");
    return boost::regex_match(input, e);
}

bool acceptOutfields(const std::string& input){
    static const boost::regex e("OUTFIELDS");
    return boost::regex_match(input, e);
}


