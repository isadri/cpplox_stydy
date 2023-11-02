#pragma once

#include <string>
#include "TokenType.hpp"

class	Token {
public:
	Token() = default;
	Token(TokenType type, const std::string& lexeme);
	Token(const Token&) = default;
	~Token();

	Token&	operator=(const Token&) = default;

	const std::string	getType() const;
	const std::string&	getLexeme() const;

private:
	static std::string	_typesNames[39];

	TokenType	_type;
	std::string	_lexeme;
};