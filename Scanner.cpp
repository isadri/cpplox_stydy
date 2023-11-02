#include "Scanner.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <sys/errno.h>

Scanner::Scanner(const std::string& source)
	: _source(source)
	, _start(0)
	, _current(0)
	, _hadError(false)
{
	_keywords["and"] = AND;
	_keywords["class"] = CLASS;
	_keywords["else"] = ELSE;
	_keywords["false"] = FALSE;
	_keywords["for"] = FOR;
	_keywords["fun"] = FUN;
	_keywords["if"] = IF;
	_keywords["nil"] = NIL;
	_keywords["or"] = OR;
	_keywords["print"] = PRINT;
	_keywords["return"] = RETURN;
	_keywords["super"] = SUPER;
	_keywords["this"] = THIS;
	_keywords["true"] = TRUE;
	_keywords["var"] = VAR;
	_keywords["while"] = WHILE;
}

Scanner::~Scanner() {}

std::list<Token>	Scanner::scanTokens() {
	while (!isAtEnd()) {
		_start = _current;
		scanToken();
	}
	addToken(END, "");
	return _tokens;
}

void	Scanner::scanToken() {
	char	c = advance();

	switch (c) {
		case '(':	addToken(RIGHT_PAREN, "(");	break;
		case ')':	addToken(LEFT_PAREN, ")");	break;
		case '{':	addToken(LEFT_BRACE, "{");	break;
		case '}':	addToken(RIGHT_BRACE, "}");	break;
		case ',':	addToken(COMMA, ",");	break;
		case '.':	addToken(DOT, ".");	break;
		case '+':	addToken(PLUS, "+");	break;
		case '-':	addToken(MINUS, "-");	break;
		case '*':	addToken(STAR, "*");	break;
		case '!':
			if (match('='))
				addToken(BANG_EQUAL, "!=");
			else
			 	addToken(BANG, "!");
			break;
		case '=':
			if (match('='))
				addToken(EQUAL_EQUAL, "==");
			else
			 	addToken(EQUAL, "=");
			break;
		case '<':
			if (match('='))
				addToken(LESS_EQUAL, "<=");
			else
			 	addToken(LESS, "<");
			break;
		case '>':
			if (match('='))
				addToken(GREATER_EQUAL, ">=");
			else
			 	addToken(GREATER, ">");
			break;
		case '/':
			if (match('/')) {
				while (peek() != '\0' && !isAtEnd())
					advance();
			} else {
				addToken(SLASH, "/");
			}
			break;
		case ' ':
			break;
		case '"':	string();	break;
		default:
		 	if (std::isdigit(c)) {
				number();
			} else if (std::isalpha(c)) {
				identifier();
			} else {
				error("Unexpected character.");
			}
			break;
	}
}

void	Scanner::addToken(TokenType type, const std::string& lexeme) {
	_tokens.push_back(Token(type, lexeme));
}

bool	Scanner::isAtEnd() const {
	return _current >= _source.length();
}

char	Scanner::advance() {
	return _source.at(_current++);
}

bool	Scanner::match(char expected) {
	if (isAtEnd() || _source.at(_current) != expected)
		return false;
	++_current;
	return true;
}

char	Scanner::peek() const {
	return isAtEnd() ? '\0' : _source.at(_current);
}

char	Scanner::peekNext() const {
	if (_current + 1 >= _source.length())
		return '\0';
	return _source.at(_current + 1);
}

void	Scanner::skipWhiteSpaces() {
	while (std::isspace(peek()))
		advance();
}

void	Scanner::number() {
	while (std::isdigit(peek()))
		advance();
	if (peek() == '.' && std::isdigit(peekNext())) {
		advance();
		while (std::isdigit(peek()))
			advance();
	}
	addToken(NUMBER, _source.substr(_start, _current - _start));
}

void	Scanner::string() {
	while (peek() != '"' && !isAtEnd())
		advance();
	if (isAtEnd()) {
		error("Unterminated string.");
		return;
	}
	advance();
	addToken(STRING, _source.substr(_start, _current - _start));
}

void	Scanner::identifier() {
	TokenType	type;
	std::string	lexeme;

	while (std::isalnum(peek()))
		advance();
	lexeme = _source.substr(_start, _current - _start);
	if (_keywords.count(lexeme) != 0)
		type = _keywords[lexeme];
	else
	 	type = IDENTIFIER;
	addToken(type, lexeme);
}

void	Scanner::error(const char* str) {
	std::cerr << str << std::endl;
	_hadError = true;
}
