#include "Grouping.hpp"

Grouping::Grouping(Expr* expression) : _expression(expression) {}

std::string Grouping::accept(Visitor& visitor) {
    return visitor.visitGroupingExpr(*this);
}

Grouping::~Grouping() {
    //delete _expression;
}

Expr&   Grouping::getExpr() const { return *_expression; }
