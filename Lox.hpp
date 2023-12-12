#pragma once

#ifndef __LOX_HPP__
#define __LOX_HPP__

#include "common.hpp"
#include "Token.hpp"
#include "Scanner.hpp"

class   Lox {
public:
    Lox() = default;
    Lox(const Lox&) = delete;
    ~Lox() = default;

    Lox&    operator=(const Lox&) = delete;

    void    runFile(const char* file);
    void    runPrompt();

private:
    void    run(const std::string& source);
    bool    readLine(std::istream& infile, std::string& line);
};

#endif