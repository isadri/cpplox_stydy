#pragma once

#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__

#include "common.hpp"
#include "Token.hpp"

class   Scanner {
public:
    Scanner(const std::string& source);
    Scanner(const Scanner&) = delete;

    Scanner&    operator=(const Scanner&) = delete;

    std::list<Token>    scanTokens();

    static std::map<std::string, TokenType> keywords;

private:
    std::string         _source;
    std::list<Token>    _tokens;
    size_t              _start;
    size_t              _current;
    size_t              _line;
    size_t              _length;

    void    scanToken();
    bool    isAtEnd();
    char    advance();
    bool    match(char expected);
    char    peek();
    char    peekNext();
    void    skipWhiteSpaces();
    void    _string();
    void    _number();
    void    _identifier();
    void    addToken(TokenType type);
    void    addToken(TokenType type, std::string& lexeme);
};

#endif