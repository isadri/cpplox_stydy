#pragma once

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "Scanner.hpp"
#include "Expr.hpp"
#include <stdarg.h>
#include "ParseException.hpp"

class   Parser {
public:
    Parser(std::list<Token> tokens);
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

    Expr*   parse();

private:
    std::list<Token>    _tokens;
    int                 _current;

    bool    match(std::initializer_list<TokenType> types);
    bool    check(TokenType type);
    Token   advance();
    bool    isAtEnd() const;
    Token   peek() const;
    Token   previous() const;
    Token   consume(TokenType type, const std::string& message);

    ParseException  error(Token token, const std::string& message);
    void            synchronize() noexcept;

    Expr*   expression();
    Expr*   equality();
    Expr*   comparison();
    Expr*   term();
    Expr*   factor();
    Expr*   unary();
    Expr*   primary();
};

#endif