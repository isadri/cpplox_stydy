#include "Expr.hpp"

Grouping::Grouping(std::shared_ptr<Expr> expression) : _expression(expression) {
}

std::string Grouping::accept(Visitor& visitor) {
    return visitor.visitGroupingExpr(*this);
}

Grouping::~Grouping() {
}

Expr&   Grouping::getExpr() const { return *_expression; }
