#pragma once

#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

#include "Expr.hpp"
#include <stdarg.h>

class   AstPrinter : public Visitor {
public:
    virtual ~AstPrinter() {}

    void            print(Expr& expr);

    virtual void    visitBinaryExpr(Binary& expr) override;
    virtual void    visitGroupingExpr(Grouping& expr) override;
    virtual void    visitLiteralExpr(Literal& expr) override;
    virtual void    visitUnaryExpr(Unary& expr) override;

    void            parenthesize(const std::string& name, Expr& expr);
    void            parenthesize(const std::string& name, Expr& expr1,
                                Expr& expr2);
};

#endif