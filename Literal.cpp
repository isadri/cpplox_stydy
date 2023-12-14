#include "Literal.hpp"

Literal::Literal(const std::string& value) : _value(value) {}

std::string Literal::accept(Visitor& visitor) {
    return visitor.visitLiteralExpr(*this);
}

const std::string&    Literal::getValue() const { return _value; }
