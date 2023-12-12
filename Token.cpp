#include "Token.hpp"

std::map<TokenType, std::string>    m = {
    {AND, "AND"},
    {CLASS, "CLASS"},
    {ELSE, "ELSE"},
    {FALSE, "FALSE"},
    {FOR, "FOR"},
    {FUN, "FUN"},
    {IF, "IF"},
    {NIL, "NIL"},
    {OR, "OR"},
    {PRINT, "PRINT"},
    {RETURN, "RETURN"},
    {SUPER, "SUPER"},
    {THIS, "THIS"},
    {TRUE, "TRUE"},
    {VAR, "VAR"},
    {WHILE, "WHILE"},
    {IDENTIFIER, "IDENTIFIER"},
    {LEFT_PAREN, "("},
    {RIGHT_PAREN, ")"},
    {LEFT_BRACE, "{"},
    {RIGHT_BRACE, "}"},
    {COMMA, ","},
    {DOT, "."},
    {MINUS, "-"},
    {PLUS, "+"},
    {SEMICOLON, ";"},
    {SLASH, "/"},
    {STAR, "*"},
    {BANG, "!"},
    {BANG_EQUAL, "!="},
    {EQUAL, "="},
    {EQUAL_EQUAL, "=="},
    {GREATER, ">"}, {GREATER_EQUAL, ">="}, {LESS, "<"}, {LESS_EQUAL, "<="},
    {STRING, "STRING"}, {NUMBER, "NUMBER"}
};

Token::Token(TokenType type, const std::string& lexeme, size_t line)
    : _type(type)
    , _lexeme(lexeme)
    , _line(line)
{
}

std::ostream&   operator<<(std::ostream& os, const Token& t) {
    std::cout << "type: " << m[t._type] << ", value: " << t._lexeme
            << ", line: " << t._line << std::endl;
    return os;
}
