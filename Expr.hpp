#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "common.hpp"
#include "Token.hpp"

template<typename T>
class   Binary;

template<typename T>
class   Grouping;

template<typename T>
class   Unary;

template<typename T>
class   Literal;

template<typename T>
class   Expr {
public:
    class   Vistor {
    public:
        std::string   visitGroupingExpr(Grouping<T>& expr);
        std::string   visitBinaryExpr(Binary<T>& expr);
        std::string   visitLiteralExpr(Literal<T>& expr);
        std::string   visitUnaryExpr(Unary<T>& expr);
    };
    virtual T   accept(Vistor& visitor) = 0;
};

#endif