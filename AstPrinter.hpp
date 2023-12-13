#pragma once

#ifndef __AST_PRINTER_HPP__
#define __AST_PRINTER_HPP__

#include "Expr.hpp"

template<typename T>
class   AstPrinter : public Expr<T>::Vistor {
public:
    std::string print(Expr<T>& expr);
    std::string visitBinaryExpr(Binary<T>& expr);
    std::string visitGroupingExpr(Grouping<T>& expr);
    std::string visitLiteralExpr(Literal<T>& expr);
    std::string visitUnaryExpr(Unary<T>& expr);

    std::string paranthesize(std::string name, Expr<T>& right, Expr<T>& left);
    std::string paranthesize(const std::string& name, Expr<T>& expr);
    std::string paranthesize(const std::string& opt, std::string name, Expr<T>& right);
};

template<typename T>
std::string AstPrinter<T>::print(Expr<T>& expr) {
    return expr.accept(*this);
}

template<typename T>
std::string AstPrinter<T>::visitBinaryExpr(Binary<T>& expr) {
    return paranthesize(expr.getOpt().getLexeme(), expr.getLeft(),
                        expr.getRight());
}

template<typename T>
std::string AstPrinter<T>::visitGroupingExpr(Grouping<T>& expr) {
    return parenthesize("group", expr.getExpre());
}

template<typename T>
std::string AstPrinter<T>::visitLiteralExpr(Literal<T>& expr) {
    if (expr.getValue() == "null")
        return "nil";
    return std::to_string(expr.getValue());
}

template<typename T>
std::string AstPrinter<T>::visitUnaryExpr(Unary<T>& expr) {
    return parenthesize(expr.getOpt().getLexeme(), expr.getRight());
}

template<typename T>
std::string AstPrinter<T>::paranthesize(std::string name, Expr<T>& right,
                                        Expr<T>& left)
{
    std::string builder;

    builder.append("(").append(name);
    builder.append(" ");
    builder.append(right.accept(*this));
    builder.append(" ");
    builder.append(left.accept(*this));
    builder.append(")");
    return builder;
}

template<typename T>
std::string AstPrinter<T>::paranthesize(const std::string& name,
                                        Expr<T>& expr)
{
    std::string builder;

    builder.append("(").append(name);
    builder.append(" ");
    builder.append(expr.accept(*this));
    builder.append(")");
    return builder;
}

#endif