#include "Parser.hpp"
#include "Lox.hpp"

Parser::Parser(std::list<Token> tokens) : _tokens(tokens), _current(0) {}

Expr*   Parser::parse() {
    try {
        return expression();
    } catch (const ParseException& pe) {
        return nullptr;
    }
}

Expr*   Parser::expression() {
    return equality();
}

Expr*   Parser::equality() {
    std::shared_ptr<Expr>   expr(comparison());

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        Token                   opt(previous());
        std::shared_ptr<Expr>   right(comparison());
        expr.reset(new Binary(expr.get(), new Token(opt), right.get()));
    }
    return expr.get();
}

Expr*   Parser::comparison() {
    std::shared_ptr<Expr>   expr(term());

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token                   opt = previous();
        std::shared_ptr<Expr>   right(term());
        expr.reset(new Binary(expr.get(), new Token(opt), right.get()));
    }
    return expr.get();
}

Expr*   Parser::term() {
    std::shared_ptr<Expr>   expr(factor());

    while (match({MINUS, PLUS})) {
        Token           opt = previous();
        std::shared_ptr<Expr>   right(factor());
        expr.reset(new Binary(expr.get(), new Token(opt), right.get()));
    }
    return expr.get();
}

Expr*   Parser::factor() {
    std::shared_ptr<Expr>   expr(unary());

    while (match({SLASH, STAR})) {
        Token                   opt = previous();
        std::shared_ptr<Expr>   right(unary());
        expr.reset(new Binary(expr.get(), new Token(opt), right.get()));
    }
    return expr.get();
}

Expr*   Parser::unary() {
    if (match({BANG, MINUS})) {
        Token                   opt = previous();
        std::shared_ptr<Expr>   right(unary());
        return new Unary(new Token(opt), right.get());
    }
    return primary();
}

Expr*   Parser::primary() {
    if (match({FALSE}))
        return new Literal("false");
    if (match({TRUE}))
        return new Literal("true");
    if (match({NIL}))
        return new Literal("nil");
    if (match({NUMBER, STRING}))
        return new Literal(previous().getLexeme());
    if (match({LEFT_PAREN})) {
        std::shared_ptr<Expr>   expr(expression());
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr.get());
    }
    throw error(peek(), "Expect expression.");
}

Token   Parser::consume(TokenType type, const std::string& message) {
    if (check(type))
        return advance();
    throw error(peek(), message);
}

ParseException  Parser::error(Token token, const std::string& message) {
    Lox::error(token, message);
    return ParseException();
}

void    Parser::synchronize() noexcept {
    advance();

    while (!isAtEnd()) {
        if (previous().getType() == SEMICOLON)
            return;
        switch (peek().getType()) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;
            default:
                break;
        }
        advance();
    }
}

bool    Parser::match(std::initializer_list<TokenType> types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool    Parser::check(TokenType type) {
    if (isAtEnd())
        return false;
    return peek().getType() == type;
}

Token   Parser::advance() {
    if (!isAtEnd())
        _current++;
    return previous();
}

bool    Parser::isAtEnd() const {
    return peek().getType() == END;
}

Token  Parser::peek() const {
    auto  it = _tokens.begin();

    std::advance(it, _current);
    return *it;
}

Token   Parser::previous() const {
    auto    it = _tokens.begin();

    std::advance(it, _current - 1);
    return *it;
}
