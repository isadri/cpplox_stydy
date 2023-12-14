#ifndef __INTERPRETER_HPP__
#define __INTERPRETER_HPP__

#include "Expr.hpp"

class   Interpreter : public Visitor {
public:
    virtual ~Interpreter() {}

    virtual std::string visitLiteralExpr(Literal& expr);
    virtual std::string visitGroupingExpr(Grouping& expr);
    virtual std::string visitUnaryExpr(Unary& expr);

    virtual std::string evaluate(Expr& expr);
};

#endif