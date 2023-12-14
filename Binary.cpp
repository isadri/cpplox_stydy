#include "Binary.hpp"

Binary::Binary(Expr* left, Token* opt, Expr* right)
    : _left(left)
    , _opt(opt)
    , _right(right)
{
}

Binary::~Binary() {
    delete _left;
    delete _opt;
    delete _right;
}

std::string Binary::accept(Visitor& visitor) {
    return visitor.visitBinaryExpr(*this);
}

Expr&   Binary::getLeft() const { return *_left; }

Token&  Binary::getOpt() const { return *_opt; }

Expr&   Binary::getRight() const { return *_right; }
