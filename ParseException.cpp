#include "ParseException.hpp"

ParseException::ParseException() {
}

std::string ParseException::toString(int nbr) {
    std::stringstream   ss;
    std::string         str;

    ss << std::dec << nbr;
    ss >> str;
    return str;
}