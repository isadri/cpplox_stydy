#pragma once

#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

#include "Expr.hpp"

class   AstPrinter : public Visitor {
public:
    virtual ~AstPrinter() {}

    std::string print(Expr& expr);

    std::string visitBinaryExpr(Binary& expr) override;
    std::string visitGroupingExpr(Grouping& expr) override;
    std::string visitLiteralExpr(Literal& expr) override;
    std::string visitUnaryExpr(Unary& expr) override;

private:
    std::string parenthesize(const std::string& name, Expr& left, Expr& right);
    std::string parenthesize(const std::string& name, Expr& expr);

    std::string accept(Visitor& visitor) override;
};

#endif