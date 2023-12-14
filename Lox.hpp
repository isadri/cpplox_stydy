#pragma once

#include "AstPrinter.hpp"
#include "Visitor.hpp"
#include "Scanner.hpp"
#include "Token.hpp"
#include "common.hpp"

class Lox {
public:
    Lox() = default;
    Lox(const Lox &) = delete;
    ~Lox() = default;

    Lox &operator=(const Lox &) = delete;

    void runFile(const char *file);
    void runPrompt();

    static void error(Token token, const std::string &message);

private:
    void run(const std::string &source);
    bool readLine(std::istream &infile, std::string &line);
};