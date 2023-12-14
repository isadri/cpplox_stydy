#include "Unary.hpp"

Unary::Unary(Token* opt, Expr* right) : _opt(opt), _right(right) {}

std::string Unary::accept(Visitor& visitor) {
    return visitor.visitUnaryExpr(*this);
}

Unary::~Unary() {
    delete _opt;
    delete _right;
}

Token&  Unary::getOpt() const { return *_opt; }

Expr&   Unary::getRight() const { return *_right; }
