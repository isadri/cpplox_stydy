#include "Expr.hpp"

Unary::Unary(std::shared_ptr<Token> opt, std::shared_ptr<Expr> right)
    : _opt(opt)
    , _right(right)
{
}

std::string Unary::accept(Visitor& visitor) {
    return visitor.visitUnaryExpr(*this);
}

Unary::~Unary() {
}

Token&  Unary::getOpt() const { return *_opt; }

Expr&   Unary::getRight() const { return *_right; }
