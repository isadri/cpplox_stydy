#include "Token.hpp"
#include "TokenType.hpp"
#include <string>

std::string	Token::_typesNames[] = {
	"LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
	"DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "BANG", "BANG_EQUAL",
	"EQUAL", "EQUAL_EQUAL", "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL",
	"IDENTIFIER", "STRING", "NUMBRE", "AND", "CLASS", "ELSE", "FALSE", "FUN",
	"FOR", "IF", "NIL", "OR", "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",
	"END"
};

Token::Token(TokenType type, const std::string& lexeme)
	: _type(type)
	, _lexeme(lexeme)
{
}

Token::~Token() {}

const std::string	Token::getType() const {
	return _typesNames[_type];
}

const std::string&	Token::getLexeme() const { return _lexeme; }
