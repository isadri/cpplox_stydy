#include "Expr.hpp"

Literal::Literal(const std::string& value) : _value(value) {}

void Literal::accept(Visitor& visitor) {
    visitor.visitLiteralExpr(*this);
}

const std::string&    Literal::getValue() const { return _value; }
