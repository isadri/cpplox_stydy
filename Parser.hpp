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

    std::shared_ptr<Expr>   parse();

private:
    std::list<Token>    _tokens;
    int                 _current;

    bool    match(std::initializer_list<TokenType> types);
    bool    check(TokenType type);
    Token   advance();
    bool    isAtEnd();
    Token   peek();
    Token   previous();
    Token   consume(TokenType type, const std::string& message);

    ParseException  error(Token token, const std::string& message);
    void            synchronize() noexcept;

    std::shared_ptr<Expr>   expression();
    std::shared_ptr<Expr>   equality();
    std::shared_ptr<Expr>   comparison();
    std::shared_ptr<Expr>   term();
    std::shared_ptr<Expr>   factor();
    std::shared_ptr<Expr>   unary();
    std::shared_ptr<Expr>   primary();
};

#endif