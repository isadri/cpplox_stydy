#pragma once

#ifndef __PARSE_EXCEPTION_HPP__
#define __PARSE_EXCEPTION_HPP__

#include "common.hpp"
#include "Token.hpp"

class   ParseException : std::exception {
public:
    ParseException();

    static std::string toString(int nbr);

private:
    std::string _errorMsg;
};

#endif