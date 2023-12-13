#pragma once


#ifndef __VISITOR_HPP
#define __VISITOR_HPP

#include "common.hpp"

class   Expr;
class   Binary;
class   Grouping;
class   Unary;

template<typename T>
class   Literal;

template<typename T>
class   Vistor {
public:
    std::string   visitGroupingExpr(Grouping& expr);
    std::string   visitBinaryExpr(Binary& expr);
    std::string   visitLiteralExpr(Literal<T>& expr);
    std::string   visitUnaryExpr(Unary& expr);

    virtual T   accept(Expr& visitor) = 0;
};

#endif