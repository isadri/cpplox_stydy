#include "Expr.hpp"

Unary::Unary(std::shared_ptr<Token> opt, std::shared_ptr<Expr> right)
    : _opt(opt)
    , _right(right)
{
}

void Unary::accept(Visitor& visitor) {
    visitor.visitUnaryExpr(*this);
}

Unary::~Unary() {
}

Token&  Unary::getOpt() const { return *_opt; }

Expr&   Unary::getRight() const { return *_right; }
