#pragma once

#ifndef __LOX_HPP__
#define __LOX_HPP__

#include "common.hpp"
#include "Token.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "AstPrinter.hpp"

class   Lox {
public:
    Lox() = default;
    Lox(const Lox&) = delete;
    ~Lox() = default;

    Lox&    operator=(const Lox&) = delete;

    void    runFile(const char* file);
    void    runPrompt();

    static void error(Token token, const std::string& message);

private:
    void    run(const std::string& source);
    bool    readLine(std::istream& infile, std::string& line);
};

#endif