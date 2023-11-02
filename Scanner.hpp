#pragma once

#include <cstddef>
#include <list>
#include <map>
#include <string>
#include "Token.hpp"
#include "TokenType.hpp"

class	Scanner {
public:
	Scanner() = delete;
	Scanner(const std::string& source);
	Scanner(const Scanner&) = delete;
	~Scanner();

	Scanner&	operator=(const Scanner&) = delete;

	std::list<Token>	scanTokens();
	void				scanToken();
	void				addToken(TokenType type, const std::string& lexeme);
	bool				isAtEnd() const;
	char				advance();
	bool				match(char expected);
	char				peek() const;
	char				peekNext() const;
	void				number();
	void				string();
	void				identifier();
	void				error(const char* str);
	void				skipWhiteSpaces();

private:
	std::string							_source;
	std::list<Token>					_tokens;
	size_t								_start;
	size_t								_current;
	bool								_hadError;

	std::map<std::string, TokenType>	_keywords;
};