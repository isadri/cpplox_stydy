#include "Scanner.hpp"

std::map<std::string, TokenType>    Scanner::keywords = {
    {"and", AND},
    {"class", CLASS},
    {"else", ELSE},
    {"false", FALSE},
    {"for", FOR},
    {"fun", FUN},
    {"if", IF},
    {"nil", NIL},
    {"or", OR},
    {"print", PRINT},
    {"return", RETURN},
    {"super", SUPER},
    {"this", THIS},
    {"true", TRUE},
    {"var", VAR},
    {"while", WHILE}
};

Scanner::Scanner(const std::string& source)
    : _source(source)
    , _start(0)
    , _current(0)
    , _line(1)
    , _length(source.length())
{
}

std::list<Token>    Scanner::scanTokens() {
    while (!isAtEnd()) {
        skipWhiteSpaces();
        _start = _current;
        scanToken();
    }
    _tokens.push_back(Token(END, "", _line));
    return _tokens;
}

void    Scanner::scanToken() {
    char    c = advance();

    switch (c) {
        case '(':   addToken(LEFT_PAREN);   break;
        case ')':   addToken(RIGHT_PAREN);  break;
        case '{':   addToken(LEFT_BRACE);   break;
        case '}':   addToken(RIGHT_BRACE);  break;
        case ',':   addToken(COMMA);        break;
        case '.':   addToken(DOT);          break;
        case '-':   addToken(MINUS);        break;
        case '+':   addToken(PLUS);         break;
        case ';':   addToken(SEMICOLON);    break;
        case '*':   addToken(STAR);         break;
        case '!':   addToken(match('=') ? BANG_EQUAL : BANG);       break;
        case '=':   addToken(match('=') ? EQUAL_EQUAL : EQUAL);     break;
        case '<':   addToken(match('=') ? LESS_EQUAL : LESS);       break;
        case '>':   addToken(match('=') ? GREATER_EQUAL : GREATER); break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken(SLASH);
            }
            break;
        case '\n':
            _line++;
            break;
        case '"':   _string();  break;
        default:
            if (std::isdigit(c)) {
                _number();
            } else if (std::isalpha(c)) {
                _identifier();
            } else {
                ErrorReporter::error(_line, "Unexpected character.");
            }
            break;
    }
}

void    Scanner::_string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            _line++;
        advance();
    }
    if (isAtEnd()) {
        ErrorReporter::error(_line, "Unterminated string.");
        return;
    }
    advance();
    std::string value = _source.substr(_start + 1, _current - _start - 2);
    addToken(STRING, value);
}

void    Scanner::_number() {
    while (std::isdigit(peek()))
        advance();
    if (peek() == '.' && std::isdigit(peekNext())) {
        advance();
        while (std::isdigit(peek()))
            advance();
    }
    addToken(NUMBER);
}

void    Scanner::_identifier() {
    while (std::isalnum(peek()))
        advance();
    std::string text = _source.substr(_start, _current - _start);
    TokenType   type;
    try {
        type = keywords.at(text);
    } catch (std::out_of_range& oor) {
        type = IDENTIFIER;
    }
    addToken(type);
}

bool    Scanner::isAtEnd() {
    return _current >= _length;
}

char    Scanner::advance() {
    return _source.at(_current++);
}

bool    Scanner::match(char expected) {
    if (isAtEnd())
        return false;
    if (_source.at(_current) != expected)
        return false;
    _current++;
    return true;
}

char    Scanner::peek() {
    if (isAtEnd())
        return '\0';
    return _source.at(_current);
}

char    Scanner::peekNext() {
    if (_current + 1 >= _length)
        return '\0';
    return _source.at(_current + 1);
}

void    Scanner::skipWhiteSpaces() {
    while (std::isspace(peek()) && peek() != '\n')
        advance();
}

void    Scanner::addToken(TokenType type) {
    std::string text = _source.substr(_start, _current - _start);
    _tokens.push_back({type, text, _line});
}

void    Scanner::addToken(TokenType type, std::string& lexeme) {
    _tokens.push_back({type, lexeme, _line});
}
