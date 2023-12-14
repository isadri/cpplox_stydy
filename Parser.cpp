#include "Parser.hpp"
#include "Lox.hpp"

Parser::Parser(std::list<Token> tokens) : _tokens(tokens), _current(0) {
}

std::shared_ptr<Expr>   Parser::parse() {
    try {
        return expression();
    } catch (const ParseException &pe) {
        return nullptr;
    }
}

std::shared_ptr<Expr>   Parser::expression() { return equality(); }

std::shared_ptr<Expr>   Parser::equality() {
    std::shared_ptr<Expr> expr(comparison());

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        std::shared_ptr<Token> opt(new Token(previous()));
        std::shared_ptr<Expr> right(comparison());

        expr = std::shared_ptr<Expr>(new Binary(expr, opt, right));
    }
    return expr;
}

std::shared_ptr<Expr>   Parser::comparison() {
    std::shared_ptr<Expr> expr(term());

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        std::shared_ptr<Token>  opt(new Token(previous()));
        std::shared_ptr<Expr>   right(term());
        expr = std::shared_ptr<Expr>(new Binary(expr, opt, right));
    }
    return expr;
}

std::shared_ptr<Expr>   Parser::term() {
    std::shared_ptr<Expr> expr(factor());


    while (match({MINUS, PLUS})) {
        std::shared_ptr<Token>  opt(new Token(previous()));
        std::shared_ptr<Expr>   right(factor());
        expr = std::shared_ptr<Expr>(new Binary(expr, opt, right));
    }
    return expr;
}

std::shared_ptr<Expr>   Parser::factor() {
    std::shared_ptr<Expr> expr(unary());

    while (match({SLASH, STAR})) {
        std::shared_ptr<Token>  opt(new Token(previous()));
        std::shared_ptr<Expr>   right(unary());
        expr = std::shared_ptr<Expr>(new Binary(expr, opt, right));
    }
    return expr;
}

std::shared_ptr<Expr>   Parser::unary() {
    if (match({BANG, MINUS})) {
        std::shared_ptr<Token>  opt(new Token(previous()));
        std::shared_ptr<Expr>   right(unary());
        return std::shared_ptr<Expr>(new Unary(opt, right));
    }
    return primary();
}

std::shared_ptr<Expr>   Parser::primary() {
    if (match({FALSE}))
        return std::shared_ptr<Expr>(new Literal("false"));
    if (match({TRUE}))
        return std::shared_ptr<Expr>(new Literal("true"));
    if (match({NIL}))
        return std::shared_ptr<Expr>(new Literal("nil"));
    if (match({NUMBER, STRING}))
        return std::shared_ptr<Expr>(new Literal(previous().getLexeme()));
    if (match({LEFT_PAREN})) {
        std::shared_ptr<Expr> expr(expression());
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return std::shared_ptr<Expr>(new Grouping(expr));
    }
    throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, const std::string &message) {
    if (check(type))
        return advance();
    throw error(peek(), message);
}

ParseException Parser::error(Token token, const std::string &message) {
    Lox::error(token, message);
    return ParseException();
}

void Parser::synchronize() noexcept {
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

bool Parser::match(std::initializer_list<TokenType> types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd())
        return false;
    return peek().getType() == type;
}

Token Parser::advance() {
    if (!isAtEnd())
        _current++;
    return previous();
}

bool Parser::isAtEnd() { return peek().getType() == END; }

Token Parser::peek() {
    auto it = _tokens.begin();

    std::advance(it, _current);
    return *it;
}

Token Parser::previous() {
  auto it = _tokens.begin();

    std::advance(it, _current - 1);
    return *it;
}
