#include "Expr.hpp"

Grouping::Grouping(std::shared_ptr<Expr> expression) : _expression(expression) {
}

void Grouping::accept(Visitor& visitor) {
    visitor.visitGroupingExpr(*this);
}

Grouping::~Grouping() {
}

Expr&   Grouping::getExpr() const { return *_expression; }
