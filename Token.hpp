#pragma once

#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include "common.hpp"

class   Token {
public:
    Token(TokenType type, const std::string& lexeme, size_t line);

    friend std::ostream&    operator<<(std::ostream& os, const Token& t);

    static std::map<TokenType, std::string>    m;

private:
    TokenType   _type;
    std::string _lexeme;
    size_t      _line;
};

#endif